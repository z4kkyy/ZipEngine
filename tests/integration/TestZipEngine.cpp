#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/ZipEngine.h"
#include "ZipEngine/FileIO.h"
#include <fstream>

TEST_CASE("ZipEngine compression and decompression", "[ZipEngine]") {
    ZipEngine::Engine zipEngine;
    ZipEngine::FileIO fileIO;

    SECTION("Compress and decompress a file") {
        // Create a test file
        std::string testContent = "This is a test file for ZipEngine compression and decompression.";
        std::string inputFile = "test_input.txt";
        std::string compressedFile = "test_compressed.zip";
        std::string decompressedFile = "test_decompressed.txt";

        std::ofstream ofs(inputFile);
        ofs << testContent;
        ofs.close();

        // Compress the file
        REQUIRE(zipEngine.compress(inputFile, compressedFile));

        // Decompress the file
        REQUIRE(zipEngine.decompress(compressedFile, decompressedFile));

        // Read the decompressed file
        std::vector<uint8_t> decompressedContent = fileIO.readFile(decompressedFile);
        std::string decompressedString(decompressedContent.begin(), decompressedContent.end());

        // Check if the decompressed content matches the original
        REQUIRE(decompressedString == testContent);

        // Clean up temporary files
        std::remove(inputFile.c_str());
        std::remove(compressedFile.c_str());
        std::remove(decompressedFile.c_str());
    }

    SECTION("Compress and decompress an empty file") {
        std::string emptyFile = "empty.txt";
        std::string compressedFile = "empty_compressed.zip";
        std::string decompressedFile = "empty_decompressed.txt";

        std::ofstream ofs(emptyFile);
        ofs.close();

        REQUIRE(zipEngine.compress(emptyFile, compressedFile));
        REQUIRE(zipEngine.decompress(compressedFile, decompressedFile));

        std::vector<uint8_t> decompressedContent = fileIO.readFile(decompressedFile);
        REQUIRE(decompressedContent.empty());

        std::remove(emptyFile.c_str());
        std::remove(compressedFile.c_str());
        std::remove(decompressedFile.c_str());
    }

    SECTION("Try to compress a non-existent file") {
        REQUIRE_FALSE(zipEngine.compress("non_existent.txt", "compressed.zip"));
    }

    SECTION("Try to decompress a non-existent file") {
        REQUIRE_FALSE(zipEngine.decompress("non_existent.zip", "decompressed.txt"));
    }
}
