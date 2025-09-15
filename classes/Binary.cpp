#include "Binary.h"
#include "BinaryDataException.h"
#include "Limits.h"

extern "C" {
#include "php.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
#include "ext-binary_arginfo.h"
}

#include <cstring>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

// External declarations for global class entries
extern zend_class_entry* binary_ce;
extern zend_class_entry* binary_data_exception_ce;
extern zend_class_entry* limits_ce;

// Helper function to throw BinaryDataException
static void throwBinaryDataException(const char* message) {
    zend_throw_exception(binary_data_exception_ce, message, 0);
}

// Helper function to check data length
void BinaryUtils::checkLength(const std::string& data, size_t needed) {
    if (data.length() < needed) {
        std::ostringstream oss;
        oss << "Not enough bytes: need " << needed << ", have " << data.length();
        throwBinaryDataException(oss.str().c_str());
    }
}

// Sign/unsign operations
int64_t BinaryUtils::signByte(int64_t value) {
    return (value << 56) >> 56;
}

int64_t BinaryUtils::unsignByte(int64_t value) {
    return value & 0xff;
}

int64_t BinaryUtils::signShort(int64_t value) {
    return (value << 48) >> 48;
}

int64_t BinaryUtils::unsignShort(int64_t value) {
    return value & 0xffff;
}

int64_t BinaryUtils::signInt(int64_t value) {
    return (value << 32) >> 32;
}

int64_t BinaryUtils::unsignInt(int64_t value) {
    return value & 0xffffffff;
}

// Byte swapping utilities
uint16_t BinaryUtils::swapBytes16(uint16_t value) {
    return ((value & 0xff) << 8) | ((value >> 8) & 0xff);
}

uint32_t BinaryUtils::swapBytes32(uint32_t value) {
    return ((value & 0xff) << 24) |
           (((value >> 8) & 0xff) << 16) |
           (((value >> 16) & 0xff) << 8) |
           ((value >> 24) & 0xff);
}

uint64_t BinaryUtils::swapBytes64(uint64_t value) {
    return ((value & 0xff) << 56) |
           (((value >> 8) & 0xff) << 48) |
           (((value >> 16) & 0xff) << 40) |
           (((value >> 24) & 0xff) << 32) |
           (((value >> 32) & 0xff) << 24) |
           (((value >> 40) & 0xff) << 16) |
           (((value >> 48) & 0xff) << 8) |
           ((value >> 56) & 0xff);
}

// Endianness flipping
int64_t BinaryUtils::flipShortEndianness(int64_t value) {
    return readLShort(writeShort(value));
}

int64_t BinaryUtils::flipIntEndianness(int64_t value) {
    return readLInt(writeInt(value));
}

int64_t BinaryUtils::flipLongEndianness(int64_t value) {
    return readLLong(writeLong(value));
}

// Boolean operations
bool BinaryUtils::readBool(const std::string& data) {
    checkLength(data, 1);
    return data[0] != '\x00';
}

std::string BinaryUtils::writeBool(bool value) {
    return std::string(1, value ? '\x01' : '\x00');
}

// Byte operations
int64_t BinaryUtils::readByte(const std::string& data) {
    checkLength(data, 1);
    return static_cast<uint8_t>(data[0]);
}

int64_t BinaryUtils::readSignedByte(const std::string& data) {
    checkLength(data, 1);
    return signByte(static_cast<uint8_t>(data[0]));
}

std::string BinaryUtils::writeByte(int64_t value) {
    return std::string(1, static_cast<char>(value & 0xff));
}

// Short operations (big-endian)
int64_t BinaryUtils::readShort(const std::string& data) {
    checkLength(data, SIZE_SHORT);
    uint16_t value = (static_cast<uint8_t>(data[0]) << 8) |
                     static_cast<uint8_t>(data[1]);
    return value;
}

int64_t BinaryUtils::readSignedShort(const std::string& data) {
    return signShort(readShort(data));
}

std::string BinaryUtils::writeShort(int64_t value) {
    uint16_t val = static_cast<uint16_t>(value);
    std::string result(2, 0);
    result[0] = static_cast<char>((val >> 8) & 0xff);
    result[1] = static_cast<char>(val & 0xff);
    return result;
}

// Short operations (little-endian)
int64_t BinaryUtils::readLShort(const std::string& data) {
    checkLength(data, SIZE_SHORT);
    uint16_t value = static_cast<uint8_t>(data[0]) |
                     (static_cast<uint8_t>(data[1]) << 8);
    return value;
}

int64_t BinaryUtils::readSignedLShort(const std::string& data) {
    return signShort(readLShort(data));
}

std::string BinaryUtils::writeLShort(int64_t value) {
    uint16_t val = static_cast<uint16_t>(value);
    std::string result(2, 0);
    result[0] = static_cast<char>(val & 0xff);
    result[1] = static_cast<char>((val >> 8) & 0xff);
    return result;
}

// Triad operations (3-byte)
int64_t BinaryUtils::readTriad(const std::string& data) {
    checkLength(data, 3);
    uint32_t value = (static_cast<uint8_t>(data[0]) << 16) |
                     (static_cast<uint8_t>(data[1]) << 8) |
                     static_cast<uint8_t>(data[2]);
    return value;
}

std::string BinaryUtils::writeTriad(int64_t value) {
    uint32_t val = static_cast<uint32_t>(value);
    std::string result(3, 0);
    result[0] = static_cast<char>((val >> 16) & 0xff);
    result[1] = static_cast<char>((val >> 8) & 0xff);
    result[2] = static_cast<char>(val & 0xff);
    return result;
}

int64_t BinaryUtils::readLTriad(const std::string& data) {
    checkLength(data, 3);
    uint32_t value = static_cast<uint8_t>(data[0]) |
                     (static_cast<uint8_t>(data[1]) << 8) |
                     (static_cast<uint8_t>(data[2]) << 16);
    return value;
}

std::string BinaryUtils::writeLTriad(int64_t value) {
    uint32_t val = static_cast<uint32_t>(value);
    std::string result(3, 0);
    result[0] = static_cast<char>(val & 0xff);
    result[1] = static_cast<char>((val >> 8) & 0xff);
    result[2] = static_cast<char>((val >> 16) & 0xff);
    return result;
}

// Int operations (big-endian)
int64_t BinaryUtils::readInt(const std::string& data) {
    checkLength(data, SIZE_INT);
    uint32_t value = (static_cast<uint8_t>(data[0]) << 24) |
                     (static_cast<uint8_t>(data[1]) << 16) |
                     (static_cast<uint8_t>(data[2]) << 8) |
                     static_cast<uint8_t>(data[3]);
    return signInt(value);
}

std::string BinaryUtils::writeInt(int64_t value) {
    uint32_t val = static_cast<uint32_t>(value);
    std::string result(4, 0);
    result[0] = static_cast<char>((val >> 24) & 0xff);
    result[1] = static_cast<char>((val >> 16) & 0xff);
    result[2] = static_cast<char>((val >> 8) & 0xff);
    result[3] = static_cast<char>(val & 0xff);
    return result;
}

// Int operations (little-endian)
int64_t BinaryUtils::readLInt(const std::string& data) {
    checkLength(data, SIZE_INT);
    uint32_t value = static_cast<uint8_t>(data[0]) |
                     (static_cast<uint8_t>(data[1]) << 8) |
                     (static_cast<uint8_t>(data[2]) << 16) |
                     (static_cast<uint8_t>(data[3]) << 24);
    return signInt(value);
}

std::string BinaryUtils::writeLInt(int64_t value) {
    uint32_t val = static_cast<uint32_t>(value);
    std::string result(4, 0);
    result[0] = static_cast<char>(val & 0xff);
    result[1] = static_cast<char>((val >> 8) & 0xff);
    result[2] = static_cast<char>((val >> 16) & 0xff);
    result[3] = static_cast<char>((val >> 24) & 0xff);
    return result;
}

// Float operations (big-endian)
double BinaryUtils::readFloat(const std::string& data) {
    checkLength(data, SIZE_FLOAT);
    union {
        uint32_t i;
        float f;
    } converter;

    converter.i = (static_cast<uint8_t>(data[0]) << 24) |
                  (static_cast<uint8_t>(data[1]) << 16) |
                  (static_cast<uint8_t>(data[2]) << 8) |
                  static_cast<uint8_t>(data[3]);

    return static_cast<double>(converter.f);
}

double BinaryUtils::readRoundedFloat(const std::string& data, int accuracy) {
    double value = readFloat(data);
    double factor = std::pow(10.0, accuracy);
    return std::round(value * factor) / factor;
}

std::string BinaryUtils::writeFloat(double value) {
    union {
        uint32_t i;
        float f;
    } converter;

    converter.f = static_cast<float>(value);

    std::string result(4, 0);
    result[0] = static_cast<char>((converter.i >> 24) & 0xff);
    result[1] = static_cast<char>((converter.i >> 16) & 0xff);
    result[2] = static_cast<char>((converter.i >> 8) & 0xff);
    result[3] = static_cast<char>(converter.i & 0xff);
    return result;
}

// Float operations (little-endian)
double BinaryUtils::readLFloat(const std::string& data) {
    checkLength(data, SIZE_FLOAT);
    union {
        uint32_t i;
        float f;
    } converter;

    converter.i = static_cast<uint8_t>(data[0]) |
                  (static_cast<uint8_t>(data[1]) << 8) |
                  (static_cast<uint8_t>(data[2]) << 16) |
                  (static_cast<uint8_t>(data[3]) << 24);

    return static_cast<double>(converter.f);
}

double BinaryUtils::readRoundedLFloat(const std::string& data, int accuracy) {
    double value = readLFloat(data);
    double factor = std::pow(10.0, accuracy);
    return std::round(value * factor) / factor;
}

std::string BinaryUtils::writeLFloat(double value) {
    union {
        uint32_t i;
        float f;
    } converter;

    converter.f = static_cast<float>(value);

    std::string result(4, 0);
    result[0] = static_cast<char>(converter.i & 0xff);
    result[1] = static_cast<char>((converter.i >> 8) & 0xff);
    result[2] = static_cast<char>((converter.i >> 16) & 0xff);
    result[3] = static_cast<char>((converter.i >> 24) & 0xff);
    return result;
}

std::string BinaryUtils::printFloat(double value) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%F", value);
    std::string result(buffer);

    size_t decimal_pos = result.find('.');
    if (decimal_pos != std::string::npos) {
        // Find the last non-zero digit after decimal point
        size_t last_nonzero = result.length() - 1;
        while (last_nonzero > decimal_pos + 1 && result[last_nonzero] == '0') {
            last_nonzero--;
        }

        // Keep the string up to the last non-zero digit (but keep at least one digit after decimal)
        if (last_nonzero > decimal_pos) {
            result = result.substr(0, last_nonzero + 1);
        }
    }

    return result;
}

// Double operations (big-endian)
double BinaryUtils::readDouble(const std::string& data) {
    checkLength(data, SIZE_DOUBLE);
    union {
        uint64_t i;
        double d;
    } converter;

    converter.i = (static_cast<uint64_t>(static_cast<uint8_t>(data[0])) << 56) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[1])) << 48) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[2])) << 40) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[3])) << 32) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[4])) << 24) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[5])) << 16) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[6])) << 8) |
                  static_cast<uint64_t>(static_cast<uint8_t>(data[7]));

    return converter.d;
}

std::string BinaryUtils::writeDouble(double value) {
    union {
        uint64_t i;
        double d;
    } converter;

    converter.d = value;

    std::string result(8, 0);
    result[0] = static_cast<char>((converter.i >> 56) & 0xff);
    result[1] = static_cast<char>((converter.i >> 48) & 0xff);
    result[2] = static_cast<char>((converter.i >> 40) & 0xff);
    result[3] = static_cast<char>((converter.i >> 32) & 0xff);
    result[4] = static_cast<char>((converter.i >> 24) & 0xff);
    result[5] = static_cast<char>((converter.i >> 16) & 0xff);
    result[6] = static_cast<char>((converter.i >> 8) & 0xff);
    result[7] = static_cast<char>(converter.i & 0xff);
    return result;
}

// Double operations (little-endian)
double BinaryUtils::readLDouble(const std::string& data) {
    checkLength(data, SIZE_DOUBLE);
    union {
        uint64_t i;
        double d;
    } converter;

    converter.i = static_cast<uint64_t>(static_cast<uint8_t>(data[0])) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[1])) << 8) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[2])) << 16) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[3])) << 24) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[4])) << 32) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[5])) << 40) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[6])) << 48) |
                  (static_cast<uint64_t>(static_cast<uint8_t>(data[7])) << 56);

    return converter.d;
}

std::string BinaryUtils::writeLDouble(double value) {
    union {
        uint64_t i;
        double d;
    } converter;

    converter.d = value;

    std::string result(8, 0);
    result[0] = static_cast<char>(converter.i & 0xff);
    result[1] = static_cast<char>((converter.i >> 8) & 0xff);
    result[2] = static_cast<char>((converter.i >> 16) & 0xff);
    result[3] = static_cast<char>((converter.i >> 24) & 0xff);
    result[4] = static_cast<char>((converter.i >> 32) & 0xff);
    result[5] = static_cast<char>((converter.i >> 40) & 0xff);
    result[6] = static_cast<char>((converter.i >> 48) & 0xff);
    result[7] = static_cast<char>((converter.i >> 56) & 0xff);
    return result;
}

// Long operations (big-endian)
int64_t BinaryUtils::readLong(const std::string& data) {
    checkLength(data, SIZE_LONG);
    uint64_t value = (static_cast<uint64_t>(static_cast<uint8_t>(data[0])) << 56) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[1])) << 48) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[2])) << 40) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[3])) << 32) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[4])) << 24) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[5])) << 16) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[6])) << 8) |
                     static_cast<uint64_t>(static_cast<uint8_t>(data[7]));
    return static_cast<int64_t>(value);
}

std::string BinaryUtils::writeLong(int64_t value) {
    uint64_t val = static_cast<uint64_t>(value);
    std::string result(8, 0);
    result[0] = static_cast<char>((val >> 56) & 0xff);
    result[1] = static_cast<char>((val >> 48) & 0xff);
    result[2] = static_cast<char>((val >> 40) & 0xff);
    result[3] = static_cast<char>((val >> 32) & 0xff);
    result[4] = static_cast<char>((val >> 24) & 0xff);
    result[5] = static_cast<char>((val >> 16) & 0xff);
    result[6] = static_cast<char>((val >> 8) & 0xff);
    result[7] = static_cast<char>(val & 0xff);
    return result;
}

// Long operations (little-endian)
int64_t BinaryUtils::readLLong(const std::string& data) {
    checkLength(data, SIZE_LONG);
    uint64_t value = static_cast<uint64_t>(static_cast<uint8_t>(data[0])) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[1])) << 8) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[2])) << 16) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[3])) << 24) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[4])) << 32) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[5])) << 40) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[6])) << 48) |
                     (static_cast<uint64_t>(static_cast<uint8_t>(data[7])) << 56);
    return static_cast<int64_t>(value);
}

std::string BinaryUtils::writeLLong(int64_t value) {
    uint64_t val = static_cast<uint64_t>(value);
    std::string result(8, 0);
    result[0] = static_cast<char>(val & 0xff);
    result[1] = static_cast<char>((val >> 8) & 0xff);
    result[2] = static_cast<char>((val >> 16) & 0xff);
    result[3] = static_cast<char>((val >> 24) & 0xff);
    result[4] = static_cast<char>((val >> 32) & 0xff);
    result[5] = static_cast<char>((val >> 40) & 0xff);
    result[6] = static_cast<char>((val >> 48) & 0xff);
    result[7] = static_cast<char>((val >> 56) & 0xff);
    return result;
}

// Variable-length integer operations
int64_t BinaryUtils::readUnsignedVarInt(const std::string& buffer, size_t& offset) {
    uint32_t value = 0;
    for (int i = 0; i <= 28; i += 7) {
        if (offset >= buffer.length()) {
            throwBinaryDataException("No bytes left in buffer");
            return 0;
        }
        uint8_t b = static_cast<uint8_t>(buffer[offset++]);
        value |= ((b & 0x7f) << i);

        if ((b & 0x80) == 0) {
            return static_cast<int64_t>(value);
        }
    }

    throwBinaryDataException("VarInt did not terminate after 5 bytes!");
    return 0;
}

int64_t BinaryUtils::readVarInt(const std::string& buffer, size_t& offset) {
    uint32_t raw = static_cast<uint32_t>(readUnsignedVarInt(buffer, offset));
    // ZigZag decoding: (n >>> 1) ^ (-(n & 1))
    int32_t temp = static_cast<int32_t>((raw >> 1) ^ (-(raw & 1)));
    return static_cast<int64_t>(temp);
}

std::string BinaryUtils::writeUnsignedVarInt(int64_t value) {
    std::string buf;
    uint32_t remaining = static_cast<uint32_t>(value) & 0xffffffff;

    for (int i = 0; i < 5; ++i) {
        if ((remaining >> 7) != 0) {
            buf += static_cast<char>(remaining | 0x80);
        } else {
            buf += static_cast<char>(remaining & 0x7f);
            return buf;
        }

        remaining = (remaining >> 7) & (0x7fffffff >> 6);
    }

    throwBinaryDataException("Value too large to be encoded as a VarInt");
    return "";
}

std::string BinaryUtils::writeVarInt(int64_t value) {
    int32_t v = static_cast<int32_t>(value << 32 >> 32);
    return writeUnsignedVarInt(static_cast<int64_t>((v << 1) ^ (v >> 31)));
}

// Variable-length long operations
int64_t BinaryUtils::readUnsignedVarLong(const std::string& buffer, size_t& offset) {
    uint64_t value = 0;
    for (int i = 0; i <= 63; i += 7) {
        if (offset >= buffer.length()) {
            throwBinaryDataException("No bytes left in buffer");
            return 0;
        }
        uint8_t b = static_cast<uint8_t>(buffer[offset++]);
        value |= (static_cast<uint64_t>(b & 0x7f) << i);

        if ((b & 0x80) == 0) {
            return static_cast<int64_t>(value);
        }
    }

    throwBinaryDataException("VarLong did not terminate after 10 bytes!");
    return 0;
}

int64_t BinaryUtils::readVarLong(const std::string& buffer, size_t& offset) {
    uint64_t raw = static_cast<uint64_t>(readUnsignedVarLong(buffer, offset));
    // ZigZag decoding: (n >>> 1) ^ (-(n & 1))
    int64_t temp = static_cast<int64_t>((raw >> 1) ^ (-(raw & 1)));
    return temp;
}

std::string BinaryUtils::writeUnsignedVarLong(int64_t value) {
    std::string buf;
    uint64_t remaining = static_cast<uint64_t>(value);

    for (int i = 0; i < 10; ++i) {
        if ((remaining >> 7) != 0) {
            buf += static_cast<char>(remaining | 0x80);
        } else {
            buf += static_cast<char>(remaining & 0x7f);
            return buf;
        }

        remaining = (remaining >> 7) & (0x7fffffffffffffffULL >> 6);
    }

    throwBinaryDataException("Value too large to be encoded as a VarLong");
    return "";
}

std::string BinaryUtils::writeVarLong(int64_t value) {
    return writeUnsignedVarLong((value << 1) ^ (value >> 63));
}

// Safe unpacking operation
std::string BinaryUtils::safeUnpack(const std::string& format, const std::string& data) {
    if (format.empty() || data.empty()) {
        throwBinaryDataException("Invalid format or data for safeUnpack");
        return "";
    }

    // Calculate expected data length based on format
    size_t expected_length = 0;
    for (char c : format) {
        switch (c) {
            case 'C': // unsigned char
            case 'c': // signed char
                expected_length += 1;
                break;
            case 'S': // unsigned short (big endian)
            case 's': // signed short (big endian)
            case 'n': // unsigned short (network/big endian)
            case 'v': // unsigned short (little endian)
                expected_length += 2;
                break;
            case 'L': // unsigned long (big endian)
            case 'l': // signed long (big endian)
            case 'N': // unsigned long (network/big endian)
            case 'V': // unsigned long (little endian)
            case 'f': // float
                expected_length += 4;
                break;
            case 'Q': // unsigned long long (big endian)
            case 'q': // signed long long (big endian)
            case 'J': // unsigned long long (big endian)
            case 'P': // unsigned long long (little endian)
            case 'd': // double
                expected_length += 8;
                break;
            default:
                break;
        }
    }

    checkLength(data, expected_length);

    return data;
}

// PHP binding functions
extern "C" {

// Sign/unsign operations
PHP_FUNCTION(binary_sign_byte) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::signByte(value));
}

PHP_FUNCTION(binary_unsign_byte) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::unsignByte(value));
}

PHP_FUNCTION(binary_sign_short) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::signShort(value));
}

PHP_FUNCTION(binary_unsign_short) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::unsignShort(value));
}

PHP_FUNCTION(binary_sign_int) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::signInt(value));
}

PHP_FUNCTION(binary_unsign_int) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::unsignInt(value));
}

// Endianness flipping
PHP_FUNCTION(binary_flip_short_endianness) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::flipShortEndianness(value));
}

PHP_FUNCTION(binary_flip_int_endianness) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::flipIntEndianness(value));
}

PHP_FUNCTION(binary_flip_long_endianness) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::flipLongEndianness(value));
}

// Boolean operations
PHP_FUNCTION(binary_read_bool) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_BOOL(BinaryUtils::readBool(str));
}

PHP_FUNCTION(binary_write_bool) {
    zend_bool value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_BOOL(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeBool(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Byte operations
PHP_FUNCTION(binary_read_byte) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readByte(str));
}

PHP_FUNCTION(binary_read_signed_byte) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readSignedByte(str));
}

PHP_FUNCTION(binary_write_byte) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeByte(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Short operations
PHP_FUNCTION(binary_read_short) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readShort(str));
}

PHP_FUNCTION(binary_read_signed_short) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readSignedShort(str));
}

PHP_FUNCTION(binary_write_short) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeShort(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_FUNCTION(binary_read_lshort) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readLShort(str));
}

PHP_FUNCTION(binary_read_signed_lshort) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readSignedLShort(str));
}

PHP_FUNCTION(binary_write_lshort) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLShort(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Static method implementations for Binary class
PHP_METHOD(Binary, signByte) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::signByte(value));
}

PHP_METHOD(Binary, unsignByte) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::unsignByte(value));
}

PHP_METHOD(Binary, signShort) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::signShort(value));
}

PHP_METHOD(Binary, unsignShort) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::unsignShort(value));
}

PHP_METHOD(Binary, signInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::signInt(value));
}

PHP_METHOD(Binary, unsignInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::unsignInt(value));
}

PHP_METHOD(Binary, readBool) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_BOOL(BinaryUtils::readBool(str));
}

PHP_METHOD(Binary, writeBool) {
    zend_bool value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_BOOL(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeBool(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readByte) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readByte(str));
}

PHP_METHOD(Binary, readSignedByte) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readSignedByte(str));
}

PHP_METHOD(Binary, writeByte) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeByte(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Short operations
PHP_METHOD(Binary, readShort) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readShort(str));
}

PHP_METHOD(Binary, readSignedShort) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readSignedShort(str));
}

PHP_METHOD(Binary, writeShort) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeShort(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readLShort) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readLShort(str));
}

PHP_METHOD(Binary, readSignedLShort) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readSignedLShort(str));
}

PHP_METHOD(Binary, writeLShort) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLShort(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Triad operations
PHP_METHOD(Binary, readTriad) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readTriad(str));
}

PHP_METHOD(Binary, writeTriad) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeTriad(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readLTriad) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readLTriad(str));
}

PHP_METHOD(Binary, writeLTriad) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLTriad(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Int operations
PHP_METHOD(Binary, readInt) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readInt(str));
}

PHP_METHOD(Binary, writeInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeInt(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readLInt) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readLInt(str));
}

PHP_METHOD(Binary, writeLInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLInt(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Float operations
PHP_METHOD(Binary, readFloat) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_DOUBLE(BinaryUtils::readFloat(str));
}

PHP_METHOD(Binary, writeFloat) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeFloat(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readLFloat) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_DOUBLE(BinaryUtils::readLFloat(str));
}

PHP_METHOD(Binary, writeLFloat) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLFloat(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Endianness flipping operations
PHP_METHOD(Binary, flipShortEndianness) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::flipShortEndianness(value));
}

PHP_METHOD(Binary, flipIntEndianness) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::flipIntEndianness(value));
}

PHP_METHOD(Binary, flipLongEndianness) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(BinaryUtils::flipLongEndianness(value));
}

// Rounded float operations
PHP_METHOD(Binary, readRoundedFloat) {
    zend_string *data;
    zend_long accuracy;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(data)
        Z_PARAM_LONG(accuracy)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_DOUBLE(BinaryUtils::readRoundedFloat(str, accuracy));
}

PHP_METHOD(Binary, readRoundedLFloat) {
    zend_string *data;
    zend_long accuracy;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(data)
        Z_PARAM_LONG(accuracy)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_DOUBLE(BinaryUtils::readRoundedLFloat(str, accuracy));
}

// Print float operation
PHP_METHOD(Binary, printFloat) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::printFloat(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Double operations
PHP_METHOD(Binary, readDouble) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_DOUBLE(BinaryUtils::readDouble(str));
}

PHP_METHOD(Binary, writeDouble) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeDouble(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readLDouble) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_DOUBLE(BinaryUtils::readLDouble(str));
}

PHP_METHOD(Binary, writeLDouble) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLDouble(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Long operations
PHP_METHOD(Binary, readLong) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readLong(str));
}

PHP_METHOD(Binary, writeLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLong(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readLLong) {
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    RETURN_LONG(BinaryUtils::readLLong(str));
}

PHP_METHOD(Binary, writeLLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeLLong(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// VarInt operations
PHP_METHOD(Binary, readVarInt) {
    zend_string *data;
    zval *offset_zval;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(data)
        Z_PARAM_ZVAL(offset_zval)
    ZEND_PARSE_PARAMETERS_END();

    // Dereference the zval if it's a reference
    ZVAL_DEREF(offset_zval);

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    size_t off = static_cast<size_t>(Z_LVAL_P(offset_zval));
    int64_t result = BinaryUtils::readVarInt(str, off);

    // Update the offset reference
    ZVAL_LONG(offset_zval, static_cast<zend_long>(off));

    RETURN_LONG(result);
}

PHP_METHOD(Binary, writeVarInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeVarInt(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readUnsignedVarInt) {
    zend_string *data;
    zval *offset_zval;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(data)
        Z_PARAM_ZVAL(offset_zval)
    ZEND_PARSE_PARAMETERS_END();

    // Dereference the zval if it's a reference
    ZVAL_DEREF(offset_zval);

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    size_t off = static_cast<size_t>(Z_LVAL_P(offset_zval));
    int64_t result = BinaryUtils::readUnsignedVarInt(str, off);

    // Update the offset reference
    ZVAL_LONG(offset_zval, static_cast<zend_long>(off));

    RETURN_LONG(result);
}

PHP_METHOD(Binary, writeUnsignedVarInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeUnsignedVarInt(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// VarLong operations
PHP_METHOD(Binary, readVarLong) {
    zend_string *data;
    zval *offset_zval;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(data)
        Z_PARAM_ZVAL(offset_zval)
    ZEND_PARSE_PARAMETERS_END();

    // Dereference the zval if it's a reference
    ZVAL_DEREF(offset_zval);

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    size_t off = static_cast<size_t>(Z_LVAL_P(offset_zval));
    int64_t result = BinaryUtils::readVarLong(str, off);

    // Update the offset reference
    ZVAL_LONG(offset_zval, static_cast<zend_long>(off));

    RETURN_LONG(result);
}

PHP_METHOD(Binary, writeVarLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeVarLong(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(Binary, readUnsignedVarLong) {
    zend_string *data;
    zval *offset_zval;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(data)
        Z_PARAM_ZVAL(offset_zval)
    ZEND_PARSE_PARAMETERS_END();

    // Dereference the zval if it's a reference
    ZVAL_DEREF(offset_zval);

    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    size_t off = static_cast<size_t>(Z_LVAL_P(offset_zval));
    int64_t result = BinaryUtils::readUnsignedVarLong(str, off);

    // Update the offset reference
    ZVAL_LONG(offset_zval, static_cast<zend_long>(off));

    RETURN_LONG(result);
}

PHP_METHOD(Binary, writeUnsignedVarLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    std::string result = BinaryUtils::writeUnsignedVarLong(value);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Safe unpacking operation
PHP_METHOD(Binary, safeUnpack) {
    zend_string *format;
    zend_string *data;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STR(format)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    std::string format_str(ZSTR_VAL(format), ZSTR_LEN(format));
    std::string data_str(ZSTR_VAL(data), ZSTR_LEN(data));

    std::string result = BinaryUtils::safeUnpack(format_str, data_str);
    RETURN_STRINGL(result.c_str(), result.length());
}

// Function table for Binary class using generated arginfo
static const zend_function_entry binary_methods[] = {
    // Sign/unsign operations
    PHP_ME(Binary, signByte, arginfo_class_Binary_signByte, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, unsignByte, arginfo_class_Binary_unsignByte, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, signShort, arginfo_class_Binary_signShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, unsignShort, arginfo_class_Binary_unsignShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, signInt, arginfo_class_Binary_signInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, unsignInt, arginfo_class_Binary_unsignInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Boolean operations
    PHP_ME(Binary, readBool, arginfo_class_Binary_readBool, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeBool, arginfo_class_Binary_writeBool, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Byte operations
    PHP_ME(Binary, readByte, arginfo_class_Binary_readByte, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readSignedByte, arginfo_class_Binary_readSignedByte, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeByte, arginfo_class_Binary_writeByte, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Short operations
    PHP_ME(Binary, readShort, arginfo_class_Binary_readShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readSignedShort, arginfo_class_Binary_readSignedShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeShort, arginfo_class_Binary_writeShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readLShort, arginfo_class_Binary_readLShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readSignedLShort, arginfo_class_Binary_readSignedLShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeLShort, arginfo_class_Binary_writeLShort, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Triad operations
    PHP_ME(Binary, readTriad, arginfo_class_Binary_readTriad, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeTriad, arginfo_class_Binary_writeTriad, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readLTriad, arginfo_class_Binary_readLTriad, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeLTriad, arginfo_class_Binary_writeLTriad, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Int operations
    PHP_ME(Binary, readInt, arginfo_class_Binary_readInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeInt, arginfo_class_Binary_writeInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readLInt, arginfo_class_Binary_readLInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeLInt, arginfo_class_Binary_writeLInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Float operations
    PHP_ME(Binary, readFloat, arginfo_class_Binary_readFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeFloat, arginfo_class_Binary_writeFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readLFloat, arginfo_class_Binary_readLFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeLFloat, arginfo_class_Binary_writeLFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readRoundedFloat, arginfo_class_Binary_readRoundedFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readRoundedLFloat, arginfo_class_Binary_readRoundedLFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, printFloat, arginfo_class_Binary_printFloat, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Double operations
    PHP_ME(Binary, readDouble, arginfo_class_Binary_readDouble, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeDouble, arginfo_class_Binary_writeDouble, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readLDouble, arginfo_class_Binary_readLDouble, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeLDouble, arginfo_class_Binary_writeLDouble, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Long operations
    PHP_ME(Binary, readLong, arginfo_class_Binary_readLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeLong, arginfo_class_Binary_writeLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readLLong, arginfo_class_Binary_readLLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeLLong, arginfo_class_Binary_writeLLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Endianness flipping operations
    PHP_ME(Binary, flipShortEndianness, arginfo_class_Binary_flipShortEndianness, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, flipIntEndianness, arginfo_class_Binary_flipIntEndianness, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, flipLongEndianness, arginfo_class_Binary_flipLongEndianness, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // VarInt operations
    PHP_ME(Binary, readVarInt, arginfo_class_Binary_readVarInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeVarInt, arginfo_class_Binary_writeVarInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readUnsignedVarInt, arginfo_class_Binary_readUnsignedVarInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeUnsignedVarInt, arginfo_class_Binary_writeUnsignedVarInt, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // VarLong operations
    PHP_ME(Binary, readVarLong, arginfo_class_Binary_readVarLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeVarLong, arginfo_class_Binary_writeVarLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, readUnsignedVarLong, arginfo_class_Binary_readUnsignedVarLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Binary, writeUnsignedVarLong, arginfo_class_Binary_writeUnsignedVarLong, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    // Safe unpacking operation
    PHP_ME(Binary, safeUnpack, arginfo_class_Binary_safeUnpack, ZEND_ACC_PRIVATE | ZEND_ACC_STATIC)
    PHP_FE_END
};

} // extern "C"

// Class initialization function
extern "C" void init_class_Binary() {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Binary", binary_methods);
    binary_ce = zend_register_internal_class(&ce);
    binary_ce->ce_flags |= ZEND_ACC_FINAL;

    // Register class constants
    zend_declare_class_constant_long(binary_ce, "SIZE_SHORT", sizeof("SIZE_SHORT")-1, BinaryUtils::SIZE_SHORT);
    zend_declare_class_constant_long(binary_ce, "SIZE_INT", sizeof("SIZE_INT")-1, BinaryUtils::SIZE_INT);
    zend_declare_class_constant_long(binary_ce, "SIZE_LONG", sizeof("SIZE_LONG")-1, BinaryUtils::SIZE_LONG);
    zend_declare_class_constant_long(binary_ce, "SIZE_FLOAT", sizeof("SIZE_FLOAT")-1, BinaryUtils::SIZE_FLOAT);
    zend_declare_class_constant_long(binary_ce, "SIZE_DOUBLE", sizeof("SIZE_DOUBLE")-1, BinaryUtils::SIZE_DOUBLE);
}

extern "C" void init_class_BinaryDataException() {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "BinaryDataException", NULL);
    binary_data_exception_ce = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException);
}


