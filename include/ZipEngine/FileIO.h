/**
 * @file FileIO.h
 * @brief Defines the FileIO class for handling file input/output operations in the ZipEngine.
 *
 * This class provides utility functions for reading from and writing to files,
 * as well as methods for reading and writing specific data types (uint8_t, uint16_t, uint32_t).
 * It also includes exception handling for file operations.
 */

#ifndef ZIP_ENGINE_FILE_IO_H
#define ZIP_ENGINE_FILE_IO_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

namespace ZipEngine {

class FileIO {
public:
    FileIO() = default;
    ~FileIO() = default;

    std::vector<uint8_t> readFile(const std::string& filename);
    void writeFile(const std::string& filename, const std::vector<uint8_t>& data);

    uint32_t readUint32(std::ifstream& file);
    uint16_t readUint16(std::ifstream& file);
    uint8_t readUint8(std::ifstream& file);

    void writeUint32(std::ofstream& file, uint32_t value);
    void writeUint16(std::ofstream& file, uint16_t value);
    void writeUint8(std::ofstream& file, uint8_t value);

    class FileIOException : public std::runtime_error {
    public:
        FileIOException(const std::string& message) : std::runtime_error(message) {}
    };
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_FILE_IO
