#ifndef ZIP_ENGINE_COMPRESSOR_H
#define ZIP_ENGINE_COMPRESSOR_H

#include <vector>
#include <string>
#include "FileHeader.h"
#include "HuffmanCoding.h"
#include "LZ77.h"
#include "CRC32.h"

namespace ZipEngine {

class Compressor {
public:
    Compressor();
    bool compressFile(const std::string& inputFile, const std::string& outputFile);
    std::vector<uint8_t> compressData(const std::vector<uint8_t>& data);

private:
    HuffmanCoding huffman;
    LZ77 lz77;
    CRC32 crc32;

    std::vector<uint8_t> deflate(const std::vector<uint8_t>& data);
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_COMPRESSOR_H
