/**
 * @file CRC32.h
 * @brief Provides a CRC32 class for calculating CRC32 checksums.
 *
 * The CRC32 class implements the 32-bit Cyclic Redundancy Check algorithm,
 * which is commonly used in data integrity verification, including in the
 * ZIP file format.
 */

#ifndef ZIP_ENGINE_CRC32_H
#define ZIP_ENGINE_CRC32_H

#include <cstdint>
#include <vector>
#include <array>


namespace ZipEngine {

class CRC32 {
public:
    CRC32();
    uint32_t calculate(const std::vector<uint8_t>& data);
    uint32_t calculate(const uint8_t* data, size_t length);

private:
    std::array<uint32_t, 256> crc_table;\
    void generate_crc_table();
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_CRC32_H
