/**
 * @file ZipEngine.h
 * @brief Main include file for the ZipEngine library.
 *
 * This header file includes all the necessary headers for using the ZipEngine library.
 * By including this file, users gain access to the entire functionality of ZipEngine,
 * including compression, decompression, file I/O operations, and utility classes.
 *
 * This centralized include file simplifies the use of the library by providing
 * a single point of inclusion for client code.
 */

#ifndef ZIP_ENGINE_H
#define ZIP_ENGINE_H

#include "ZipEngine/ZipEngine.h"
#include "ZipEngine/Compressor.h"
#include "ZipEngine/Decompressor.h"
#include "ZipEngine/FileHeader.h"
#include "ZipEngine/HuffmanCoding.h"
#include "ZipEngine/LZ77.h"
#include "ZipEngine/CRC32.h"
#include "ZipEngine/FileIO.h"
#include "ZipEngine/BitStream.h"

#endif
