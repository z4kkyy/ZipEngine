#include "ZipEngine/BitStream.h"

namespace ZipEngine {

BitStream::BitStream() : bitPosition(0) {}

BitStream::BitStream(const std::vector<uint8_t>& data) : buffer(data), bitPosition(0) {}

void BitStream::writeBit(bool bit) {
    ensureCapacity(1);
    size_t byteIndex = bitPosition / 8;
    size_t bitIndex = 7 - (bitPosition % 8);

    if (bit) {
        buffer[byteIndex] |= (1 << bitIndex);
    } else {
        buffer[byteIndex] &= ~(1 << bitIndex);
    }

    bitPosition++;
}

void BitStream::writeBits(uint32_t bits, int count) {
    for (int i = count - 1; i >= 0; i--) {
        writeBit((bits & (1 << i)) != 0);
    }
}

bool BitStream::readBit() {
    if (bitPosition >= buffer.size() * 8) {
        throw std::out_of_range("Attempt to read past end of BitStream");
    }

    size_t byteIndex = bitPosition / 8;
    size_t bitIndex = 7 - (bitPosition % 8);

    bitPosition++;
    return (buffer[byteIndex] & (1 << bitIndex)) != 0;
}

uint32_t BitStream::readBits(int count) {
    uint32_t result = 0;
    for (int i = 0; i < count; i++) {
        result = (result << 1) | (readBit() ? 1 : 0);
    }
    return result;
}

void BitStream::writeBytes(const std::vector<uint8_t>& bytes) {
    for (uint8_t byte : bytes) {
        writeBits(byte, 8);
    }
}

std::vector<uint8_t> BitStream::readBytes(size_t count) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < count; i++) {
        result.push_back(static_cast<uint8_t>(readBits(8)));
    }
    return result;
}

const std::vector<uint8_t>& BitStream::getData() const {
    return buffer;
}

void BitStream::clear() {
    buffer.clear();
    bitPosition = 0;
}

size_t BitStream::getBitPosition() const {
    return bitPosition;
}

void BitStream::setBitPosition(size_t position) {
    if (position > buffer.size() * 8) {
        throw std::out_of_range("Attempt to set bit position past end of BitStream");
    }
    bitPosition = position;
}

void BitStream::ensureCapacity(size_t bitsNeeded) {
    size_t totalBitsNeeded = bitPosition + bitsNeeded;
    size_t bytesNeeded = (totalBitsNeeded + 7) / 8; // round up
    if (buffer.size() < bytesNeeded) {
        buffer.resize(bytesNeeded, 0);
    }
}

} // namespace ZipEngine
