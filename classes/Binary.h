#ifndef BINARY_H
#define BINARY_H

extern "C" {
#include "php.h"
}

#include <cstdint>
#include <string>

extern zend_class_entry* binary_ce;

class BinaryUtils {
public:
    // Size constants
    static const int SIZE_SHORT = 2;
    static const int SIZE_INT = 4;
    static const int SIZE_LONG = 8;
    static const int SIZE_FLOAT = 4;
    static const int SIZE_DOUBLE = 8;

    // Sign/unsign operations
    static int64_t signByte(int64_t value);
    static int64_t unsignByte(int64_t value);
    static int64_t signShort(int64_t value);
    static int64_t unsignShort(int64_t value);
    static int64_t signInt(int64_t value);
    static int64_t unsignInt(int64_t value);

    // Endianness flipping
    static int64_t flipShortEndianness(int64_t value);
    static int64_t flipIntEndianness(int64_t value);
    static int64_t flipLongEndianness(int64_t value);

    // Boolean operations
    static bool readBool(const std::string& data);
    static std::string writeBool(bool value);

    // Byte operations
    static int64_t readByte(const std::string& data);
    static int64_t readSignedByte(const std::string& data);
    static std::string writeByte(int64_t value);

    // Short operations (big-endian)
    static int64_t readShort(const std::string& data);
    static int64_t readSignedShort(const std::string& data);
    static std::string writeShort(int64_t value);

    // Short operations (little-endian)
    static int64_t readLShort(const std::string& data);
    static int64_t readSignedLShort(const std::string& data);
    static std::string writeLShort(int64_t value);

    // Triad operations (3-byte)
    static int64_t readTriad(const std::string& data);
    static std::string writeTriad(int64_t value);
    static int64_t readLTriad(const std::string& data);
    static std::string writeLTriad(int64_t value);

    // Int operations
    static int64_t readInt(const std::string& data);
    static std::string writeInt(int64_t value);
    static int64_t readLInt(const std::string& data);
    static std::string writeLInt(int64_t value);

    // Float operations
    static double readFloat(const std::string& data);
    static double readRoundedFloat(const std::string& data, int accuracy);
    static std::string writeFloat(double value);
    static double readLFloat(const std::string& data);
    static double readRoundedLFloat(const std::string& data, int accuracy);
    static std::string writeLFloat(double value);
    static std::string printFloat(double value);

    // Double operations
    static double readDouble(const std::string& data);
    static std::string writeDouble(double value);
    static double readLDouble(const std::string& data);
    static std::string writeLDouble(double value);

    // Long operations
    static int64_t readLong(const std::string& data);
    static std::string writeLong(int64_t value);
    static int64_t readLLong(const std::string& data);
    static std::string writeLLong(int64_t value);

    // Variable-length integer operations
    static int64_t readVarInt(const std::string& buffer, size_t& offset);
    static int64_t readUnsignedVarInt(const std::string& buffer, size_t& offset);
    static std::string writeVarInt(int64_t value);
    static std::string writeUnsignedVarInt(int64_t value);

    // Variable-length long operations
    static int64_t readVarLong(const std::string& buffer, size_t& offset);
    static int64_t readUnsignedVarLong(const std::string& buffer, size_t& offset);
    static std::string writeVarLong(int64_t value);
    static std::string writeUnsignedVarLong(int64_t value);

    // Safe unpacking operation
    static std::string safeUnpack(const std::string& format, const std::string& data);

private:
    static void checkLength(const std::string& data, size_t needed);
    static uint16_t swapBytes16(uint16_t value);
    static uint32_t swapBytes32(uint32_t value);
    static uint64_t swapBytes64(uint64_t value);
};

#endif // BINARY_H
