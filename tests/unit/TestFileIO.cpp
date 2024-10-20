#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ZipEngine/FileIO.h"
#include <fstream>
#include <cstdio>

TEST_CASE("FileIO operations", "[FileIO]") {
    ZipEngine::FileIO fileIO;
    const std::string testFileName = "test_file.bin";

    SECTION("Write and read file") {
        std::vector<uint8_t> testData = {0x01, 0x02, 0x03, 0x04, 0x05};
        fileIO.writeFile(testFileName, testData);

        auto readData = fileIO.readFile(testFileName);
        REQUIRE(readData == testData);

        std::remove(testFileName.c_str());
    }

    SECTION("Read and write integers") {
        std::ofstream outFile(testFileName, std::ios::binary);
        fileIO.writeUint32(outFile, 0x12345678);
        fileIO.writeUint16(outFile, 0xABCD);
        fileIO.writeUint8(outFile, 0xEF);
        outFile.close();

        std::ifstream inFile(testFileName, std::ios::binary);
        REQUIRE(fileIO.readUint32(inFile) == 0x12345678);
        REQUIRE(fileIO.readUint16(inFile) == 0xABCD);
        REQUIRE(fileIO.readUint8(inFile) == 0xEF);
        inFile.close();

        std::remove(testFileName.c_str());
    }

    SECTION("File not found exception") {
        REQUIRE_THROWS_AS(fileIO.readFile("non_existent_file.bin"), ZipEngine::FileIO::FileIOException);
    }
}
