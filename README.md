# ZipEngine

ZipEngine is a custom implementation of a compression and decompression library inspired by the ZIP file format. It uses a combination of LZ77 and Huffman coding algorithms to achieve efficient compression.

## Important Note

**The zip files produced by this program are not compatible with standard ZIP software.** Although they use the `.zip` extension, they cannot be decompressed using general-purpose ZIP utilities. Only the ZipEngine program can correctly decompress files it has compressed.

## Complexity Analysis

### Time Complexity

The overall time complexity of the compression and decompression processes is O(n), where n is the size of the input data. This can be broken down as follows:

1. LZ77 Compression: O(n)
   - The sliding window approach takes linear time to process the input.

2. Huffman Coding: O(n + k log k)
   - Building the frequency table: O(n)
   - Building the Huffman tree: O(k log k), where k is the number of unique symbols (maximum 256 for byte data)
   - Encoding the data: O(n)

3. CRC32 Calculation: O(n)

Since k is bounded by a constant (256), the overall time complexity remains O(n).

### Space Complexity

The space complexity is O(n), where n is the size of the input data. This includes:

1. LZ77: O(W), where W is the window size (constant)
2. Huffman Coding: O(k), where k is the number of unique symbols (maximum 256)
3. Input/Output buffers: O(n)

## Compilation and Usage

### Compiling the Tests

To compile and run the tests, use the following commands:

```bash
g++ -std=c++17 -I./include -I./tests tests/integration/TestZipEngine.cpp src/core/*.cpp src/algorithms/*.cpp src/util/*.cpp -o TestZipEngine
./TestZipEngine
```

### Compiling the Main Program

To compile the main ZipEngine program, use:

```bash
g++ -std=c++17 -I./include src/main.cpp src/core/*.cpp src/algorithms/*.cpp src/util/*.cpp -o ZipEngine
```

### Usage

The ZipEngine program accepts three arguments: the operation (compress or decompress), the input file path, and the output file path.

To compress a file:

```bash
./ZipEngine compress <input_file> <output_file.zip>
```

To decompress a file:

```bash
./ZipEngine decompress <input_file.zip> <output_file>
```

Replace `<input_file>`, `<output_file.zip>`, and `<output_file>` with your actual file paths.

Examples:

```bash
./ZipEngine compress input.txt output.zip
./ZipEngine decompress output.zip output.txt
```
