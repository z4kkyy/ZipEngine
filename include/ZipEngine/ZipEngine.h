/**
 * @file ZipEngine.h
 * @brief Defines the main Engine class for the ZipEngine library.
 *
 * This class provides the high-level interface for compressing and decompressing files
 * using the ZipEngine library. It encapsulates the compression and decompression processes.
 */

#ifndef ZIP_ENGINE_H
#define ZIP_ENGINE_H

#include <string>
#include "Compressor.h"
#include "Decompressor.h"

namespace ZipEngine {

class Engine {
public:
    Engine();
    bool compress(const std::string& inputFile, const std::string& outputFile);
    bool decompress(const std::string& inputFile, const std::string& outputFile);
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_H
