#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/Compressor.h"
#include "ZipEngine/Decompressor.h"
#include "ZipEngine/FileIO.h"
#include <fstream>
#include <stdexcept>

TEST_CASE("Decompressor functionality", "[Decompressor]") {
    ZipEngine::Compressor compressor;
    ZipEngine::Decompressor decompressor;
    ZipEngine::FileIO fileIO;

    SECTION("Decompress valid compressed file") {
        std::string inputFile = "test_input.txt";
        std::string compressedFile = "test_compressed.zip";
        std::string decompressedFile = "test_decompressed.txt";

        // Create a test input file
        std::ofstream input(inputFile);
        input << "This is a test file for decompression. It contains some repetitive text to test compression efficiency.";
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

    // SECTION("Attempt to decompress invalid file") {
    //     std::string invalidFile = "invalid_compressed.zip";
    //     std::string decompressedFile = "invalid_decompressed.txt";

    //     // Create an invalid compressed file
    //     std::ofstream invalid(invalidFile, std::ios::binary);
    //     invalid << "This is not a valid compressed file";
    //     invalid.close();

    //     REQUIRE_THROWS_AS(decompressor.decompressFile(invalidFile, decompressedFile), std::runtime_error);

    //     // Clean up
    //     std::remove(invalidFile.c_str());
    // }

    SECTION("Decompress empty compressed file") {
        std::string inputFile = "empty_input.txt";
        std::string compressedFile = "empty_compressed.zip";
        std::string decompressedFile = "empty_decompressed.txt";

        // Create an empty input file
        std::ofstream input(inputFile);
        input.close();

        REQUIRE(compressor.compressFile(inputFile, compressedFile));
        REQUIRE(decompressor.decompressFile(compressedFile, decompressedFile));

        auto decompressedData = fileIO.readFile(decompressedFile);
        REQUIRE(decompressedData.empty());

        // Clean up
        std::remove(inputFile.c_str());
        std::remove(compressedFile.c_str());
        std::remove(decompressedFile.c_str());
    }
}
