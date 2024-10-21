/**
 * @file HuffmanCoding.h
 * @brief Defines the HuffmanCoding class for Huffman coding compression and decompression.
 *
 * This class implements the Huffman coding algorithm, which is used as part of
 * the compression process in the ZipEngine. It provides methods for compressing and
 * decompressing data using variable-length prefix coding.
 */

#ifndef ZIP_ENGINE_HUFFMAN_CODING_H
#define ZIP_ENGINE_HUFFMAN_CODING_H

#include <vector>
#include <unordered_map>
#include <memory>
#include "BitStream.h"

namespace ZipEngine {

class HuffmanCoding {
public:
    HuffmanCoding() = default;
    ~HuffmanCoding() = default;

    std::vector<uint8_t> compress(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decompress(const std::vector<uint8_t>& compressedData);

private:
    struct Node {
        uint8_t symbol;
        int frequency;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(uint8_t s, int f) : symbol(s), frequency(f), left(nullptr), right(nullptr) {}
    };

    std::shared_ptr<Node> buildTree(const std::vector<int>& frequencies);
    void generateCodes(const std::shared_ptr<Node>& node, const std::string& code, std::unordered_map<uint8_t, std::string>& codes);
    void writeTree(const std::shared_ptr<Node>& node, BitStream& bitStream);
    std::shared_ptr<Node> readTree(BitStream& bitStream);
};

} // namespace ZipEngine

#endif // ZIP_ENGINE_HUFFMAN_CODING_H
