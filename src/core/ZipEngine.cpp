#include "ZipEngine/ZipEngine.h"
#include <iostream>

namespace ZipEngine {

Engine::Engine() {}

bool Engine::compress(const std::string& inputFile, const std::string& outputFile) {
    try {
        Compressor compressor;
        return compressor.compressFile(inputFile, outputFile);
    } catch (const std::exception& e) {
        std::cerr << "Compression error: " << e.what() << std::endl;
        return false;
    }
}

bool Engine::decompress(const std::string& inputFile, const std::string& outputFile) {
    try {
        Decompressor decompressor;
        return decompressor.decompressFile(inputFile, outputFile);
    } catch (const std::exception& e) {
        std::cerr << "Decompression error: " << e.what() << std::endl;
        return false;
    }
}

} // namespace ZipEngine
