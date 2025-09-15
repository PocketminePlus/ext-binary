#ifndef BINARY_STREAM_H
#define BINARY_STREAM_H

extern "C" {
#include "php.h"
}

#include <string>
#include <cstdint>

extern zend_class_entry* binary_stream_ce;

class BinaryStreamUtils {
public:
    // Constructor data
    struct StreamData {
        std::string buffer;
        size_t offset;
        
        StreamData(const std::string& buf = "", size_t off = 0) : buffer(buf), offset(off) {}
    };

    // Stream management
    static void rewind(StreamData& stream);
    static void setOffset(StreamData& stream, size_t offset);
    static size_t getOffset(const StreamData& stream);
    static std::string getBuffer(const StreamData& stream);
    static std::string get(StreamData& stream, size_t length);
    static std::string getRemaining(StreamData& stream);
    static void put(StreamData& stream, const std::string& data);
    static bool feof(const StreamData& stream);

    // Boolean operations
    static bool getBool(StreamData& stream);
    static void putBool(StreamData& stream, bool value);

    // Byte operations
    static int64_t getByte(StreamData& stream);
    static void putByte(StreamData& stream, int64_t value);

    // Short operations
    static int64_t getShort(StreamData& stream);
    static int64_t getSignedShort(StreamData& stream);
    static void putShort(StreamData& stream, int64_t value);
    static int64_t getLShort(StreamData& stream);
    static int64_t getSignedLShort(StreamData& stream);
    static void putLShort(StreamData& stream, int64_t value);

    // Triad operations
    static int64_t getTriad(StreamData& stream);
    static void putTriad(StreamData& stream, int64_t value);
    static int64_t getLTriad(StreamData& stream);
    static void putLTriad(StreamData& stream, int64_t value);

    // Int operations
    static int64_t getInt(StreamData& stream);
    static void putInt(StreamData& stream, int64_t value);
    static int64_t getLInt(StreamData& stream);
    static void putLInt(StreamData& stream, int64_t value);

    // Float operations
    static double getFloat(StreamData& stream);
    static double getRoundedFloat(StreamData& stream, int accuracy);
    static void putFloat(StreamData& stream, double value);
    static double getLFloat(StreamData& stream);
    static double getRoundedLFloat(StreamData& stream, int accuracy);
    static void putLFloat(StreamData& stream, double value);

    // Double operations
    static double getDouble(StreamData& stream);
    static void putDouble(StreamData& stream, double value);
    static double getLDouble(StreamData& stream);
    static void putLDouble(StreamData& stream, double value);

    // Long operations
    static int64_t getLong(StreamData& stream);
    static void putLong(StreamData& stream, int64_t value);
    static int64_t getLLong(StreamData& stream);
    static void putLLong(StreamData& stream, int64_t value);

    // Variable-length operations
    static int64_t getUnsignedVarInt(StreamData& stream);
    static void putUnsignedVarInt(StreamData& stream, int64_t value);
    static int64_t getVarInt(StreamData& stream);
    static void putVarInt(StreamData& stream, int64_t value);
    static int64_t getUnsignedVarLong(StreamData& stream);
    static void putUnsignedVarLong(StreamData& stream, int64_t value);
    static int64_t getVarLong(StreamData& stream);
    static void putVarLong(StreamData& stream, int64_t value);
};

#endif // BINARY_STREAM_H
