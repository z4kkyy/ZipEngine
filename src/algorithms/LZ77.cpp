#include "ZipEngine/LZ77.h"
#include <algorithm>
#include <stdexcept>

namespace ZipEngine {

LZ77::LZ77(size_t windowSize, size_t lookAheadBufferSize)
    : windowSize(windowSize), lookAheadBufferSize(lookAheadBufferSize) {}

std::vector<uint8_t> LZ77::compress(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> compressed;
    size_t currentPos = 0;

    while (currentPos < data.size()) {
        Token token = findLongestMatch(data, currentPos);

        if (token.length >= 3 && token.distance > 0) {
            // set the flag bit to 1 for match token
            uint8_t flag = 1;
            compressed.push_back(flag);
            compressed.push_back(token.distance >> 8);
            compressed.push_back(token.distance & 0xFF);
            compressed.push_back(token.length);
            currentPos += token.length;
        } else {
            // set the flag bit to 0 for literal token
            uint8_t flag = 0;
            compressed.push_back(flag);
            compressed.push_back(data[currentPos]);
            currentPos += 1;
        }
    }

    return compressed;
}

std::vector<uint8_t> LZ77::decompress(const std::vector<uint8_t>& compressedData) {
    std::vector<uint8_t> decompressed;
    size_t currentPos = 0;

    while (currentPos < compressedData.size()) {
        uint8_t flag = compressedData[currentPos++];

        if (flag == 1) { // match token
            if (currentPos + 2 >= compressedData.size()) {
                throw std::runtime_error("Compressed data is corrupted");
            }
            uint16_t distance = (compressedData[currentPos] << 8) | compressedData[currentPos + 1];
            uint8_t length = compressedData[currentPos + 2];
            currentPos += 3;

            if (distance == 0 || distance > decompressed.size()) {
                throw std::runtime_error("Invalid distance in compressed data");
            }

            for (size_t i = 0; i < length; ++i) {
                decompressed.push_back(decompressed[decompressed.size() - distance]);
            }
        } else { // literal token
            if (currentPos >= compressedData.size()) {
                throw std::runtime_error("Compressed data is corrupted");
            }
            decompressed.push_back(compressedData[currentPos++]);
        }
    }

    return decompressed;
}

LZ77::Token LZ77::findLongestMatch(const std::vector<uint8_t>& data, size_t currentPos) {
    size_t windowStart = (currentPos > windowSize) ? (currentPos - windowSize) : 0;
    size_t lookaheadEnd = std::min(currentPos + lookAheadBufferSize, data.size());

    size_t bestMatchDistance = 0;
    size_t bestMatchLength = 0;

    for (size_t i = windowStart; i < currentPos; i++) {
        size_t matchLength = 0;
        while (currentPos + matchLength < lookaheadEnd &&
               data[i + matchLength] == data[currentPos + matchLength] &&
               matchLength < 255) {
            matchLength++;
        }

        if (matchLength > bestMatchLength) {
            bestMatchDistance = currentPos - i;
            bestMatchLength = matchLength;
        }
    }

    uint8_t nextChar = (currentPos + bestMatchLength < data.size()) ?
                       data[currentPos + bestMatchLength] : 0;

    return Token(static_cast<uint16_t>(bestMatchDistance),
                 static_cast<uint8_t>(bestMatchLength),
                 nextChar);
}

} // namespace ZipEngine
