/**
 * @file BitStream.h
 * @brief Provides a BitStream class for bit-level operations on data.
 *
 * The BitStream class allows reading and writing of data at the bit level,
 * which is crucial for various compression algorithms. It supports operations
 * such as reading/writing individual bits, multiple bits, and byte sequences.
*/

#ifndef ZIP_ENGINE_BIT_STREAM_H
#define ZIP_ENGINE_BIT_STREAM_H

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace ZipEngine {

class BitStream {
public:
    BitStream();
    explicit BitStream(const std::vector<uint8_t>& data);

    void writeBit(bool bit);
    void writeBits(uint32_t bits, int count);
    bool readBit();
    uint32_t readBits(int count);

    void writeBytes(const std::vector<uint8_t>& bytes);
    std::vector<uint8_t> readBytes(size_t count);

    const std::vector<uint8_t>& getData() const;
    void clear();
    size_t getBitPosition() const;
    void setBitPosition(size_t position);

private:
    std::vector<uint8_t> buffer;
    size_t bitPosition;

    void ensureCapacity(size_t bitsNeeded);

};

} // namespace ZipEngine

#endif // ZIP_ENGINE_BIT_STREAM_H
