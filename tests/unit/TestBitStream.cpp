#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/BitStream.h"

TEST_CASE("BitStream operations", "[BitStream]") {
    ZipEngine::BitStream bs;

    SECTION("Write and read single bits") {
        bs.writeBit(1);
        bs.writeBit(0);
        bs.writeBit(1);
        bs.setBitPosition(0);
        REQUIRE(bs.readBit() == true);
        REQUIRE(bs.readBit() == false);
        REQUIRE(bs.readBit() == true);
    }

    SECTION("Write and read multiple bits") {
        bs.clear();
        bs.writeBits(0b10110, 5);
        bs.setBitPosition(0);
        REQUIRE(bs.readBits(5) == 0b10110);
    }

    SECTION("Write and read bytes") {
        bs.clear();
        std::vector<uint8_t> data = {0xA5, 0x5A};
        bs.writeBytes(data);
        bs.setBitPosition(0);
        auto readData = bs.readBytes(2);
        REQUIRE(readData == data);
    }
}
