#include "ZipEngine/FileHeader.h"
#include <stdexcept>
#include <cstring>
#include <algorithm>

namespace ZipEngine {

FileHeader::FileHeader() : signature(0x04034B50), versionNeeded(20), flags(0),
    compressionMethod(0), lastModTime(0), lastModDate(0), crc32(0),
    compressedSize(0), uncompressedSize(0), filenameLength(0), extraFieldLength(0) {}

// Getters
uint32_t FileHeader::getSignature() const { return signature; }
uint16_t FileHeader::getVersionNeeded() const { return versionNeeded; }
uint16_t FileHeader::getFlags() const { return flags; }
uint16_t FileHeader::getCompressionMethod() const { return compressionMethod; }
uint16_t FileHeader::getLastModTime() const { return lastModTime; }
uint16_t FileHeader::getLastModDate() const { return lastModDate; }
uint32_t FileHeader::getCRC32() const { return crc32; }
uint32_t FileHeader::getCompressedSize() const { return compressedSize; }
uint32_t FileHeader::getUncompressedSize() const { return uncompressedSize; }
uint16_t FileHeader::getFilenameLength() const { return filenameLength; }
uint16_t FileHeader::getExtraFieldLength() const { return extraFieldLength; }
std::string FileHeader::getFilename() const { return filename; }
std::vector<uint8_t> FileHeader::getExtraField() const { return extraField; }

// Setters
void FileHeader::setVersionNeeded(uint16_t version) { versionNeeded = version; }
void FileHeader::setFlags(uint16_t f) { flags = f; }
void FileHeader::setCompressionMethod(uint16_t method) { compressionMethod = method; }
void FileHeader::setLastModTime(uint16_t time) { lastModTime = time; }
void FileHeader::setLastModDate(uint16_t date) { lastModDate = date; }
void FileHeader::setCRC32(uint32_t crc) { crc32 = crc; }
void FileHeader::setCompressedSize(uint32_t size) { compressedSize = size; }
void FileHeader::setUncompressedSize(uint32_t size) { uncompressedSize = size; }
void FileHeader::setFilename(const std::string& name) {
    filename = name;
    // std::replace(filename.begin(), filename.end(), '\\', '/');
    filenameLength = static_cast<uint16_t>(filename.length());
}
void FileHeader::setExtraField(const std::vector<uint8_t>& extra) {
    extraField = extra;
    extraFieldLength = static_cast<uint16_t>(extra.size());
}

std::vector<uint8_t> FileHeader::serialize() const {
    std::vector<uint8_t> result(30 + filenameLength + extraFieldLength);
    size_t offset = 0;

    auto writeUint32 = [&](uint32_t value) {
        result[offset++] = value & 0xFF;
        result[offset++] = (value >> 8) & 0xFF;
        result[offset++] = (value >> 16) & 0xFF;
        result[offset++] = (value >> 24) & 0xFF;
    };

    auto writeUint16 = [&](uint16_t value) {
        result[offset++] = value & 0xFF;
        result[offset++] = (value >> 8) & 0xFF;
    };

    writeUint32(signature);
    writeUint16(versionNeeded);
    writeUint16(flags);
    writeUint16(compressionMethod);
    writeUint16(lastModTime);
    writeUint16(lastModDate);
    writeUint32(crc32);
    writeUint32(compressedSize);
    writeUint32(uncompressedSize);
    writeUint16(filenameLength);
    writeUint16(extraFieldLength);

    std::copy(filename.begin(), filename.end(), result.begin() + offset);
    offset += filenameLength;
    std::copy(extraField.begin(), extraField.end(), result.begin() + offset);

    return result;
}

void FileHeader::deserialize(const std::vector<uint8_t>& data) {
    if (data.size() < 30) {
        throw std::runtime_error("Invalid file header data");
    }

    size_t offset = 0;

    auto readUint32 = [&]() -> uint32_t {
        uint32_t value = data[offset] | (data[offset + 1] << 8) | (data[offset + 2] << 16) | (data[offset + 3] << 24);
        offset += 4;
        return value;
    };

    auto readUint16 = [&]() -> uint16_t {
        uint16_t value = data[offset] | (data[offset + 1] << 8);
        offset += 2;
        return value;
    };

    signature = readUint32();
    versionNeeded = readUint16();
    flags = readUint16();
    compressionMethod = readUint16();
    lastModTime = readUint16();
    lastModDate = readUint16();
    crc32 = readUint32();
    compressedSize = readUint32();
    uncompressedSize = readUint32();
    filenameLength = readUint16();
    extraFieldLength = readUint16();

    if (data.size() < 30 + filenameLength + extraFieldLength) {
        throw std::runtime_error("Invalid file header data");
    }

    filename = std::string(reinterpret_cast<const char*>(data.data() + offset), filenameLength);
    offset += filenameLength;
    extraField = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + extraFieldLength);
}

} // namespace ZipEngine
