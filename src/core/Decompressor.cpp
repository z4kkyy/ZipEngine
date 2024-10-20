#include "ZipEngine/Decompressor.h"
#include "ZipEngine/FileIO.h"
#include <iostream>
#include <stdexcept>

namespace ZipEngine {

Decompressor::Decompressor() : lz77(32768, 258) {}

bool Decompressor::decompressFile(const std::string& inputFile, const std::string& outputFile) {
    try {
        FileIO fileIO;
        std::vector<uint8_t> inputData = fileIO.readFile(inputFile);

        FileHeader header;
        header.deserialize(inputData);

        if (header.getCompressionMethod() != 8) {
            throw std::runtime_error("Unsupported compression method");
        }

        size_t headerSize = 30 + header.getFilenameLength() + header.getExtraFieldLength();
        std::vector<uint8_t> compressedData(inputData.begin() + headerSize, inputData.end());

        std::vector<uint8_t> decompressedData = decompressData(compressedData, header.getUncompressedSize());

        uint32_t calculatedCRC = crc32.calculate(decompressedData);
        if (calculatedCRC != header.getCRC32()) {
            throw std::runtime_error("CRC32 check failed");
        }

        fileIO.writeFile(outputFile, decompressedData);

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error decompressing file: " << e.what() << std::endl;
        return false;
    }
}

std::vector<uint8_t> Decompressor::decompressData(const std::vector<uint8_t>& compressedData, size_t uncompressedSize) {
    return inflate(compressedData, uncompressedSize);
}

std::vector<uint8_t> Decompressor::inflate(const std::vector<uint8_t>& compressedData, size_t uncompressedSize) {
    auto huffmanDecompressed = huffman.decompress(compressedData);
    auto lz77Decompressed = lz77.decompress(huffmanDecompressed);

    if (lz77Decompressed.size() != uncompressedSize) {
        throw std::runtime_error("Decompressed size mismatch");
    }

    return lz77Decompressed;
}

} // namespace ZipEngine
