#include "ZipEngine/ZipEngine.h"
#include "ZipEngine/Compressor.h"
#include "ZipEngine/Decompressor.h"

#include <iostream>

namespace ZipEngine {

Engine::Engine() {}

bool Engine::compress(const std::string& inputFile, const std::string& outputFile) {
    Compressor compressor;
    return conpressor.conpressFile(inputFile, outputFile);
}

bool Engine::decompress(const std::string& inputFile, const std::string& outputFile) {
    Decompressor decompressor;
    return decompressor.decompressFile(inputFile, outputFile);
}

} // namespace ZipEngine
