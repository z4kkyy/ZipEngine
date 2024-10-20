#include "ZipEngine/HuffmanCoding.h"
#include <queue>
#include <algorithm>

namespace ZipEngine {

std::vector<uint8_t> HuffmanCoding::compress(const std::vector<uint8_t>& data) {
    if (data.empty()) {
        return std::vector<uint8_t>();
    }

    std::vector<int> frequencies(256, 0);
    for (uint8_t byte : data) {
        frequencies[byte]++;
    }

    auto root = buildTree(frequencies);
    std::unordered_map<uint8_t, std::string> codes;
    generateCodes(root, "", codes);

    BitStream bitStream;
    writeTree(root, bitStream);

    bitStream.writeBits(data.size(), 32);

    for (uint8_t byte : data) {
        for (char bit : codes[byte]) {
            bitStream.writeBit(bit == '1');
        }
    }

    return bitStream.getData();
}

std::vector<uint8_t> HuffmanCoding::decompress(const std::vector<uint8_t>& compressedData) {
    if (compressedData.empty()) {
        return std::vector<uint8_t>();
    }

    BitStream bitStream(compressedData);
    auto root = readTree(bitStream);

    uint32_t originalSize = bitStream.readBits(32);

    std::vector<uint8_t> decompressedData;
    decompressedData.reserve(originalSize);

    auto current = root;
    while (decompressedData.size() < originalSize) {
        if (!current->left && !current->right) {
            decompressedData.push_back(current->symbol);
            current = root;
        } else {
            current = bitStream.readBit() ? current->right : current->left;
        }
    }

    return decompressedData;
}

std::shared_ptr<HuffmanCoding::Node> HuffmanCoding::buildTree(const std::vector<int>& frequencies) {
    auto cmp = [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
        return a->frequency > b->frequency;
    };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(cmp)> pq(cmp);

    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            pq.push(std::make_shared<Node>(static_cast<uint8_t>(i), frequencies[i]));
        }
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto parent = std::make_shared<Node>(0, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    return pq.empty() ? nullptr : pq.top();
}

void HuffmanCoding::generateCodes(const std::shared_ptr<Node>& node, const std::string& code, std::unordered_map<uint8_t, std::string>& codes) {
    if (node->left == nullptr && node->right == nullptr) {
        codes[node->symbol] = code;
    } else {
        if (node->left) generateCodes(node->left, code + "0", codes);
        if (node->right) generateCodes(node->right, code + "1", codes);
    }
}

void HuffmanCoding::writeTree(const std::shared_ptr<Node>& node, BitStream& bitStream) {
    if (node->left == nullptr && node->right == nullptr) {
        bitStream.writeBit(true);
        bitStream.writeBits(node->symbol, 8);
    } else {
        bitStream.writeBit(false);
        writeTree(node->left, bitStream);
        writeTree(node->right, bitStream);
    }
}

std::shared_ptr<HuffmanCoding::Node> HuffmanCoding::readTree(BitStream& bitStream) {
    if (bitStream.readBit()) {
        uint8_t symbol = static_cast<uint8_t>(bitStream.readBits(8));
        return std::make_shared<Node>(symbol, 0);
    } else {
        auto node = std::make_shared<Node>(0, 0);
        node->left = readTree(bitStream);
        node->right = readTree(bitStream);
        return node;
    }
}

} // namespace ZipEngine
