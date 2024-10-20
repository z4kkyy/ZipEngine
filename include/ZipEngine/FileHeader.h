#ifndef ZIP_ENGINE_FILE_HEADER_H
#define ZIP_ENGINE_FILE_HEADER_H

#include <string>
#include <cstdint>
#include <vector>

namespace ZipEngine {

class FileHeader {
public:
    FileHeader();

    // Getters
    uint32_t getSignature() const;
    uint16_t getVersionNeeded() const;
    uint16_t getFlags() const;
    uint16_t getCompressionMethod() const;
    uint16_t getLastModTime() const;
    uint16_t getLastModDate() const;
    uint32_t getCRC32() const;
    uint32_t getCompressedSize() const;
    uint32_t getUncompressedSize() const;
    uint16_t getFilenameLength() const;
    uint16_t getExtraFieldLength() const;
    std::string getFilename() const;
    std::vector<uint8_t> getExtraField() const;

    // Setters
    void setVersionNeeded(uint16_t version);
    void setFlags(uint16_t flags);
    void setCompressionMethod(uint16_t method);
    void setLastModTime(uint16_t time);
    void setLastModDate(uint16_t date);
    void setCRC32(uint32_t crc);
    void setCompressedSize(uint32_t size);
    void setUncompressedSize(uint32_t size);
    void setFilename(const std::string& filename);
    void setExtraField(const std::vector<uint8_t>& extraField);

    std::vector<uint8_t> serialize() const;
    void deserialize(const std::vector<uint8_t>& data);

private:
    uint32_t signature;
    uint16_t versionNeeded;
    uint16_t flags;
    uint16_t compressionMethod;
    uint16_t lastModTime;
    uint16_t lastModDate;
    uint32_t crc32;
    uint32_t compressedSize;
    uint32_t uncompressedSize;
    uint16_t filenameLength;
    uint16_t extraFieldLength;
    std::string filename;
    std::vector<uint8_t> extraField;
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_FILE_HEADER_H
