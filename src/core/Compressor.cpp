#include "ZipEngine/Compressor.h"
#include "ZipEngine/FileIO.h"
#include <iostream>
#include <chrono>

namespace ZipEngine {

Compressor::Compressor() : lz77(32768, 258) {}

bool Compressor::compressFile(const std::string& inputFile, const std::string& outputFile) {
    try {
        FileIO fileIO;
        std::vector<uint8_t> inputData = fileIO.readFile(inputFile);

        auto compressedData = compressData(inputData);

        FileHeader header;
        header.setFilename(inputFile);
        header.setCompressionMethod(8);  // 8 represents the Deflate algorithm
        header.setCompressedSize(compressedData.size());
        header.setUncompressedSize(inputData.size());
        header.setCRC32(crc32.calculate(inputData));

        // Get current time for last modified time/date
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&in_time_t);
        uint16_t modTime = (tm->tm_hour << 11) | (tm->tm_min << 5) | (tm->tm_sec / 2);
        uint16_t modDate = ((tm->tm_year - 80) << 9) | ((tm->tm_mon + 1) << 5) | tm->tm_mday;
        header.setLastModTime(modTime);
        header.setLastModDate(modDate);

        std::vector<uint8_t> headerData = header.serialize();

        std::vector<uint8_t> outputData;
        outputData.insert(outputData.end(), headerData.begin(), headerData.end());
        outputData.insert(outputData.end(), compressedData.begin(), compressedData.end());

        fileIO.writeFile(outputFile, outputData);

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error compressing file: " << e.what() << std::endl;
        return false;
    }
}

std::vector<uint8_t> Compressor::compressData(const std::vector<uint8_t>& data) {
    return deflate(data);
}

std::vector<uint8_t> Compressor::deflate(const std::vector<uint8_t>& data) {
    auto lz77Compressed = lz77.compress(data);
    return huffman.compress(lz77Compressed);
}

} // namespace ZipEngine
