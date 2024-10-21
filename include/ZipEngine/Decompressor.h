/**
 * @file Decompressor.h
 * @brief Defines the Decompressor class for data decompression in the ZipEngine.
 *
 * This class implements the decompression algorithm used in the ZipEngine.
 * It reverses the compression process, combining Huffman decoding and LZ77 decompression.
 */

#ifndef ZIP_ENGINE_DECOMPRESSOR_H
#define ZIP_ENGINE_DECOMPRESSOR_H

#include <vector>
#include <string>
#include "FileHeader.h"
#include "HuffmanCoding.h"
#include "LZ77.h"
#include "CRC32.h"

namespace ZipEngine {

class Decompressor {
public:
    Decompressor();
    bool decompressFile(const std::string& inputFile, const std::string& outputFile);
    std::vector<uint8_t> decompressData(const std::vector<uint8_t>& compressedData, size_t uncompressedSize);

private:
    HuffmanCoding huffman;
    LZ77 lz77;
    CRC32 crc32;

    std::vector<uint8_t> inflate(const std::vector<uint8_t>& compressedData, size_t uncompressedSize);
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_DECOMPRESSOR_H
