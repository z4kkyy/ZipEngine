#include "ZipEngine/ZipEngine.h"
#include <iostream>
#include <string>

void printUsage() {
    std::cout << "Usage: ZipEngine [compress|decompress] <input_file> <output_file>" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage();
        return 1;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    ZipEngine::Engine zipEngine;
    bool success = false;

    if (mode == "compress") {
        success = zipEngine.compress(inputFile, outputFile);
    } else if (mode == "decompress") {
        success = zipEngine.decompress(inputFile, outputFile);
    } else {
        printUsage();
        return 1;
    }

    if (success) {
        std::cout << "Operation completed successfully." << std::endl;
        return 0;
    } else {
        std::cout << "Operation failed." << std::endl;
        return 1;
    }
}
