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
