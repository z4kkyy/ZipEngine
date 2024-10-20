#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/CRC32.h"

TEST_CASE("CRC32 calculation", "[CRC32]") {
    ZipEngine::CRC32 crc32;

    SECTION("Empty input") {
        std::vector<uint8_t> data;
        REQUIRE(crc32.calculate(data) == 0x00000000);
    }

    SECTION("Known input") {
        std::vector<uint8_t> data = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        REQUIRE(crc32.calculate(data) == 0xCBF43926);
    }

    SECTION("Another known input") {
        std::vector<uint8_t> data = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
        REQUIRE(crc32.calculate(data) == 0x4A17B156);
    }
}
