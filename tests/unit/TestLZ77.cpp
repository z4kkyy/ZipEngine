#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/LZ77.h"

TEST_CASE("LZ77 compression and decompression", "[LZ77]") {
    ZipEngine::LZ77 lz77;

    SECTION("Empty input") {
        std::vector<uint8_t> data;
        auto compressed = lz77.compress(data);
        auto decompressed = lz77.decompress(compressed);
        REQUIRE(decompressed == data);
    }

    SECTION("Simple repetitive input") {
        std::vector<uint8_t> data = {'a', 'b', 'c', 'a', 'b', 'c', 'a', 'b', 'c', 'd'};
        auto compressed = lz77.compress(data);
        auto decompressed = lz77.decompress(compressed);
        REQUIRE(decompressed == data);
        // REQUIRE(compressed.size() < data.size());
    }

    SECTION("Long repetitive input") {
        std::vector<uint8_t> data(1000, 'A');
        auto compressed = lz77.compress(data);
        auto decompressed = lz77.decompress(compressed);
        REQUIRE(decompressed == data);
        // REQUIRE(compressed.size() < data.size());
    }

    SECTION("Random data") {
        std::vector<uint8_t> data(1000);
        for (auto& byte : data) {
            byte = static_cast<uint8_t>(rand() % 256);
        }
        auto compressed = lz77.compress(data);
        auto decompressed = lz77.decompress(compressed);
        REQUIRE(decompressed == data);
    }
}

// // TODO
// TEST_CASE("LZ77 error handling", "[LZ77]") {
//     ZipEngine::LZ77 lz77;

//     SECTION("Corrupted compressed data") {
//         std::vector<uint8_t> corruptedData = {0, 0, 5, 'A'};  // Invalid compressed data
//         REQUIRE_THROWS_AS(lz77.decompress(corruptedData), std::runtime_error);
//     }

//     SECTION("Invalid distance in compressed data") {
//         std::vector<uint8_t> invalidData = {0xFF, 0xFF, 1, 'A'};  // Distance larger than decompressed size
//         REQUIRE_THROWS_AS(lz77.decompress(invalidData), std::runtime_error);
//     }
// }
