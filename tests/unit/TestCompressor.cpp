#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/Compressor.h"
#include "ZipEngine/Decompressor.h"
#include "ZipEngine/FileIO.h"
#include <fstream>

TEST_CASE("Compressor functionality", "[Compressor]") {
    ZipEngine::Compressor compressor;
    ZipEngine::Decompressor decompressor;
    ZipEngine::FileIO fileIO;

    SECTION("Compress and decompress small text") {
        std::string inputFile = "test_input.txt";
        std::string compressedFile = "test_compressed.zip";
        std::string decompressedFile = "test_decompressed.txt";

        // Create a test input file
        std::ofstream input(inputFile);
        input << "Hello, world! This is a test file for compression.";
        input.close();

        REQUIRE(compressor.compressFile(inputFile, compressedFile));
        REQUIRE(decompressor.decompressFile(compressedFile, decompressedFile));

        auto originalData = fileIO.readFile(inputFile);
        auto decompressedData = fileIO.readFile(decompressedFile);

        REQUIRE(originalData == decompressedData);

        // Clean up
        std::remove(inputFile.c_str());
        std::remove(compressedFile.c_str());
        std::remove(decompressedFile.c_str());
    }

    SECTION("Compress and decompress binary data") {
        std::vector<uint8_t> testData(1000);
        for (size_t i = 0; i < testData.size(); ++i) {
            testData[i] = static_cast<uint8_t>(i % 256);
        }

        auto compressedData = compressor.compressData(testData);
        auto decompressedData = decompressor.decompressData(compressedData, testData.size());

        REQUIRE(testData == decompressedData);
        REQUIRE(compressedData.size() < testData.size());
    }

    SECTION("Compress empty file") {
        std::string inputFile = "empty_input.txt";
        std::string compressedFile = "empty_compressed.zip";
        std::string decompressedFile = "empty_decompressed.txt";

        // Create an empty input file
        std::ofstream input(inputFile);
        input.close();

        REQUIRE(compressor.compressFile(inputFile, compressedFile));
        REQUIRE(decompressor.decompressFile(compressedFile, decompressedFile));

        auto originalData = fileIO.readFile(inputFile);
        auto decompressedData = fileIO.readFile(decompressedFile);

        REQUIRE(originalData.empty());
        REQUIRE(decompressedData.empty());

        // Clean up
        std::remove(inputFile.c_str());
        std::remove(compressedFile.c_str());
        std::remove(decompressedFile.c_str());
    }
}
