#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/BitStream.h"
#include "ZipEngine/HuffmanCoding.h"

TEST_CASE("HuffmanCoding compression and decompression", "[HuffmanCoding]") {
    ZipEngine::HuffmanCoding huffman;

    SECTION("Compress and decompress simple string") {
        std::vector<uint8_t> original = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
        auto compressed = huffman.compress(original);
        auto decompressed = huffman.decompress(compressed);
        REQUIRE(original == decompressed);
    }

    SECTION("Compression reduces size for repetitive data") {
        std::vector<uint8_t> original(1000, 'A');  // 1000 'A' characters
        auto compressed = huffman.compress(original);
        REQUIRE(compressed.size() < original.size());
    }

    SECTION("Handle empty input") {
        std::vector<uint8_t> empty;
        auto compressed = huffman.compress(empty);
        auto decompressed = huffman.decompress(compressed);
        REQUIRE(decompressed.empty());
    }

    SECTION("Handle all unique characters") {
        std::vector<uint8_t> allUnique;
        for (int i = 0; i < 256; i++) {
            allUnique.push_back(static_cast<uint8_t>(i));
        }
        auto compressed = huffman.compress(allUnique);
        auto decompressed = huffman.decompress(compressed);
        REQUIRE(allUnique == decompressed);
    }

    SECTION("Compress and decompress large random data") {
        std::vector<uint8_t> largeData(10000);
        for (auto& byte : largeData) {
            byte = static_cast<uint8_t>(rand() % 256);
        }
        auto compressed = huffman.compress(largeData);
        auto decompressed = huffman.decompress(compressed);
        REQUIRE(largeData == decompressed);
    }

    SECTION("Compress and decompress with many repeated sequences") {
        std::vector<uint8_t> repeatedData;
        for (int i = 0; i < 1000; i++) {
            repeatedData.insert(repeatedData.end(), {'A', 'B', 'C', 'D', 'E'});
        }
        auto compressed = huffman.compress(repeatedData);
        auto decompressed = huffman.decompress(compressed);
        REQUIRE(repeatedData == decompressed);
        REQUIRE(compressed.size() < repeatedData.size());
    }
}
