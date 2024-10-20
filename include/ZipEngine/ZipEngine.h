#ifdef ZIP_ENGINE_CORE_H
#define ZIP_ENGINE_CORE_H

#include <string>

namespace ZipEngine {

class Engine {
public:
    Engine();
    bool compress(const std::string& inputFile, const std::string& outputFile);
    bool decompress(const std::string& inputFile, const std::string& outputFile);
};

} // namespace ZipEngine

#endif
