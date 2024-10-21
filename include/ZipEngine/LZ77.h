/**
 * @file LZ77.h
 * @brief Defines the LZ77 class for LZ77 compression and decompression.
 *
 * This class implements the LZ77 (Lempel-Ziv 77) algorithm, which is used as part of
 * the compression process in the ZipEngine. It provides methods for compressing and
 * decompressing data using sliding window technique.
 */

#ifndef ZIP_ENGINE_LZ77_H
#define ZIP_ENGINE_LZ77_H

#include <vector>
#include <cstdint>

namespace ZipEngine {

class LZ77 {
public:
    LZ77(size_t windowSize = 32768, size_t lookAheadBufferSize = 258);

    std::vector<uint8_t> compress(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& compressedData);

private:
    size_t windowSize;
    size_t lookAheadBufferSize;

    struct Token {
        uint16_t distance;
        uint8_t length;
        uint8_t nextChar;

        Token(uint16_t d, uint8_t l, uint8_t c) : distance(d), length(l), nextChar(c) {}
    };

    Token findLongestMatch(const std::vector<uint8_t>& data, size_t currentPos);
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_LZ77_H
