#include "ZipEngine/CRC32.h"

namespace ZipEngine {

CRC32::CRC32() {
    generate_crc_table();
}

void CRC32::generate_crc_table() {
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t crc = i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc = crc >> 1;
            }
        }
        crc_table[i] = crc;
    }
}

uint32_t CRC32::calculate(const std::vector<uint8_t>& data) {
    return calculate(data.data(), data.size());
}

uint32_t CRC32::calculate(const uint8_t* data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc = crc_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
    }
    return ~crc; // Final XOR with 0xFFFFFFFF
}

} // namespace ZipEngine
