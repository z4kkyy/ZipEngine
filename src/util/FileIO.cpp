#include "ZipEngine/FileIO.h"
#include <algorithm>

namespace ZipEngine {

std::vector<uint8_t> FileIO::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw FileIO::FileIOException("Unable to open file for reading: " + filename);
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    if (!file) {
        throw FileIO::FileIOException("Error reading file: " + filename);
    }

    return buffer;
}

void FileIO::writeFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw FileIO::FileIOException("Unable to open file for writing: " + filename);
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size());

    if (!file) {
        throw FileIO::FileIOException("Error writing file: " + filename);
    }
}

uint32_t FileIO::readUint32(std::ifstream& file) {
    uint32_t value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (!file) {
        throw FileIO::FileIOException("Error reading uint32");
    }
    return value;
}

uint16_t FileIO::readUint16(std::ifstream& file) {
    uint16_t value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (!file) {
        throw FileIO::FileIOException("Error reading uint16");
    }
    return value;
}

uint8_t FileIO::readUint8(std::ifstream& file) {
    uint8_t value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (!file) {
        throw FileIO::FileIOException("Error reading uint8");
    }
    return value;
}

void FileIO::writeUint32(std::ofstream& file, uint32_t value) {
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    if (!file) {
        throw FileIO::FileIOException("Error writing uint32");
    }
}

void FileIO::writeUint16(std::ofstream& file, uint16_t value) {
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    if (!file) {
        throw FileIO::FileIOException("Error writing uint32");
    }
}

void FileIO::writeUint8(std::ofstream& file, uint8_t value) {
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    if (!file) {
        throw FileIO::FileIOException("Error writing uint32");
    }
}

} // namespace ZipEngine

