#include "BinaryStream.h"
#include "Binary.h"
#include "BinaryDataException.h"

extern "C" {
#include "php.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
#include "../ext-binary_arginfo.h"
}

#include <sstream>

// External declarations for global class entries
extern zend_class_entry* binary_stream_ce;
extern zend_class_entry* binary_data_exception_ce;

// Helper function to throw BinaryDataException
static void throwBinaryDataException(const char* message) {
    zend_throw_exception(binary_data_exception_ce, message, 0);
}

// Stream management
void BinaryStreamUtils::rewind(StreamData& stream) {
    stream.offset = 0;
}

void BinaryStreamUtils::setOffset(StreamData& stream, size_t offset) {
    stream.offset = offset;
}

size_t BinaryStreamUtils::getOffset(const StreamData& stream) {
    return stream.offset;
}

std::string BinaryStreamUtils::getBuffer(const StreamData& stream) {
    return stream.buffer;
}

std::string BinaryStreamUtils::get(StreamData& stream, size_t length) {
    if (length == 0) {
        return "";
    }

    size_t remaining = stream.buffer.length() - stream.offset;
    if (remaining < length) {
        std::ostringstream oss;
        oss << "Not enough bytes left in buffer: need " << length << ", have " << remaining;
        throwBinaryDataException(oss.str().c_str());
        return "";
    }

    // Match PocketMine logic: optimize for single byte reads
    if (length == 1) {
        char result = stream.buffer[stream.offset];
        stream.offset++;
        return std::string(1, result);
    } else {
        std::string result = stream.buffer.substr(stream.offset, length);
        stream.offset += length;
        return result;
    }
}

std::string BinaryStreamUtils::getRemaining(StreamData& stream) {
    size_t buflen = stream.buffer.length();
    if (stream.offset >= buflen) {
        throwBinaryDataException("No bytes left to read");
        return "";
    }

    // Get remaining data and update offset to end (match PocketMine behavior)
    std::string result = stream.buffer.substr(stream.offset);
    stream.offset = buflen;
    return result;
}

void BinaryStreamUtils::put(StreamData& stream, const std::string& data) {
    // Match original PHP behavior: simply append to buffer
    stream.buffer += data;
}

bool BinaryStreamUtils::feof(const StreamData& stream) {
    // Match PocketMine logic: !isset($this->buffer[$this->offset])
    return stream.offset >= stream.buffer.length();
}

// Boolean operations
bool BinaryStreamUtils::getBool(StreamData& stream) {
    std::string data = get(stream, 1);
    return data[0] != '\x00';
}

void BinaryStreamUtils::putBool(StreamData& stream, bool value) {
    // Match original PHP behavior: append directly to buffer
    if (value) {
        stream.buffer += '\x01';
    } else {
        stream.buffer += '\x00';
    }
}

// Byte operations
int64_t BinaryStreamUtils::getByte(StreamData& stream) {
    std::string data = get(stream, 1);
    return static_cast<uint8_t>(data[0]);
}

void BinaryStreamUtils::putByte(StreamData& stream, int64_t value) {
    // Match original PHP behavior: append directly to buffer
    stream.buffer += static_cast<char>(value & 0xff);
}

// Short operations
int64_t BinaryStreamUtils::getShort(StreamData& stream) {
    return BinaryUtils::readShort(get(stream, 2));
}

int64_t BinaryStreamUtils::getSignedShort(StreamData& stream) {
    return BinaryUtils::readSignedShort(get(stream, 2));
}

void BinaryStreamUtils::putShort(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeShort(value);
}

int64_t BinaryStreamUtils::getLShort(StreamData& stream) {
    return BinaryUtils::readLShort(get(stream, 2));
}

int64_t BinaryStreamUtils::getSignedLShort(StreamData& stream) {
    return BinaryUtils::readSignedLShort(get(stream, 2));
}

void BinaryStreamUtils::putLShort(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeLShort(value);
}

// Triad operations
int64_t BinaryStreamUtils::getTriad(StreamData& stream) {
    return BinaryUtils::readTriad(get(stream, 3));
}

void BinaryStreamUtils::putTriad(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeTriad(value);
}

int64_t BinaryStreamUtils::getLTriad(StreamData& stream) {
    return BinaryUtils::readLTriad(get(stream, 3));
}

void BinaryStreamUtils::putLTriad(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeLTriad(value);
}

// Int operations
int64_t BinaryStreamUtils::getInt(StreamData& stream) {
    return BinaryUtils::readInt(get(stream, 4));
}

void BinaryStreamUtils::putInt(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeInt(value);
}

int64_t BinaryStreamUtils::getLInt(StreamData& stream) {
    return BinaryUtils::readLInt(get(stream, 4));
}

void BinaryStreamUtils::putLInt(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeLInt(value);
}

// Float operations
double BinaryStreamUtils::getFloat(StreamData& stream) {
    return BinaryUtils::readFloat(get(stream, 4));
}

double BinaryStreamUtils::getRoundedFloat(StreamData& stream, int accuracy) {
    return BinaryUtils::readRoundedFloat(get(stream, 4), accuracy);
}

void BinaryStreamUtils::putFloat(StreamData& stream, double value) {
    stream.buffer += BinaryUtils::writeFloat(value);
}

double BinaryStreamUtils::getLFloat(StreamData& stream) {
    return BinaryUtils::readLFloat(get(stream, 4));
}

double BinaryStreamUtils::getRoundedLFloat(StreamData& stream, int accuracy) {
    return BinaryUtils::readRoundedLFloat(get(stream, 4), accuracy);
}

void BinaryStreamUtils::putLFloat(StreamData& stream, double value) {
    stream.buffer += BinaryUtils::writeLFloat(value);
}

// Double operations
double BinaryStreamUtils::getDouble(StreamData& stream) {
    return BinaryUtils::readDouble(get(stream, 8));
}

void BinaryStreamUtils::putDouble(StreamData& stream, double value) {
    stream.buffer += BinaryUtils::writeDouble(value);
}

double BinaryStreamUtils::getLDouble(StreamData& stream) {
    return BinaryUtils::readLDouble(get(stream, 8));
}

void BinaryStreamUtils::putLDouble(StreamData& stream, double value) {
    stream.buffer += BinaryUtils::writeLDouble(value);
}

// Long operations
int64_t BinaryStreamUtils::getLong(StreamData& stream) {
    return BinaryUtils::readLong(get(stream, 8));
}

void BinaryStreamUtils::putLong(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeLong(value);
}

int64_t BinaryStreamUtils::getLLong(StreamData& stream) {
    return BinaryUtils::readLLong(get(stream, 8));
}

void BinaryStreamUtils::putLLong(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeLLong(value);
}

// Variable-length operations
int64_t BinaryStreamUtils::getUnsignedVarInt(StreamData& stream) {
    return BinaryUtils::readUnsignedVarInt(stream.buffer, stream.offset);
}

void BinaryStreamUtils::putUnsignedVarInt(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeUnsignedVarInt(value);
}

int64_t BinaryStreamUtils::getVarInt(StreamData& stream) {
    return BinaryUtils::readVarInt(stream.buffer, stream.offset);
}

void BinaryStreamUtils::putVarInt(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeVarInt(value);
}

int64_t BinaryStreamUtils::getUnsignedVarLong(StreamData& stream) {
    return BinaryUtils::readUnsignedVarLong(stream.buffer, stream.offset);
}

void BinaryStreamUtils::putUnsignedVarLong(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeUnsignedVarLong(value);
}

int64_t BinaryStreamUtils::getVarLong(StreamData& stream) {
    return BinaryUtils::readVarLong(stream.buffer, stream.offset);
}

void BinaryStreamUtils::putVarLong(StreamData& stream, int64_t value) {
    stream.buffer += BinaryUtils::writeVarLong(value);
}

// PHP object structure for BinaryStream
struct binary_stream_object {
    BinaryStreamUtils::StreamData stream_data;
    zend_object std;
};

static inline binary_stream_object* binary_stream_from_obj(zend_object* obj) {
    return reinterpret_cast<binary_stream_object*>(
        reinterpret_cast<char*>(obj) - XtOffsetOf(binary_stream_object, std)
    );
}

#define Z_BINARY_STREAM_P(zv) binary_stream_from_obj(Z_OBJ_P(zv))

// PHP methods for BinaryStream class
extern "C" {

PHP_METHOD(BinaryStream, __construct) {
    zend_string* buffer = nullptr;
    zend_long offset = 0;

    ZEND_PARSE_PARAMETERS_START(0, 2)
        Z_PARAM_OPTIONAL
        Z_PARAM_STR(buffer)
        Z_PARAM_LONG(offset)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);

    if (buffer) {
        obj->stream_data.buffer = std::string(ZSTR_VAL(buffer), ZSTR_LEN(buffer));
    }
    obj->stream_data.offset = static_cast<size_t>(offset);
}

PHP_METHOD(BinaryStream, rewind) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::rewind(obj->stream_data);
}

PHP_METHOD(BinaryStream, setOffset) {
    zend_long offset;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(offset)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::setOffset(obj->stream_data, static_cast<size_t>(offset));
}

PHP_METHOD(BinaryStream, getOffset) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(static_cast<zend_long>(BinaryStreamUtils::getOffset(obj->stream_data)));
}

PHP_METHOD(BinaryStream, getBuffer) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    std::string buffer = BinaryStreamUtils::getBuffer(obj->stream_data);
    RETURN_STRINGL(buffer.c_str(), buffer.length());
}

PHP_METHOD(BinaryStream, get) {
    zend_long length;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(length)
    ZEND_PARSE_PARAMETERS_END();

    // Match PocketMine validation: check for negative length
    if (length < 0) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "Length must be positive", 0);
        RETURN_NULL();
    }

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    std::string result = BinaryStreamUtils::get(obj->stream_data, static_cast<size_t>(length));
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(BinaryStream, getRemaining) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    std::string result = BinaryStreamUtils::getRemaining(obj->stream_data);
    RETURN_STRINGL(result.c_str(), result.length());
}

PHP_METHOD(BinaryStream, put) {
    zend_string* data;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    std::string str(ZSTR_VAL(data), ZSTR_LEN(data));
    BinaryStreamUtils::put(obj->stream_data, str);
}

PHP_METHOD(BinaryStream, feof) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_BOOL(BinaryStreamUtils::feof(obj->stream_data));
}

// Boolean operations
PHP_METHOD(BinaryStream, getBool) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_BOOL(BinaryStreamUtils::getBool(obj->stream_data));
}

PHP_METHOD(BinaryStream, putBool) {
    zval* value_zval;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(value_zval)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    bool value = zend_is_true(value_zval);

    BinaryStreamUtils::putBool(obj->stream_data, value);
}

// Byte operations
PHP_METHOD(BinaryStream, getByte) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getByte(obj->stream_data));
}

PHP_METHOD(BinaryStream, putByte) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putByte(obj->stream_data, value);
}

// Short operations
PHP_METHOD(BinaryStream, getShort) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getShort(obj->stream_data));
}

PHP_METHOD(BinaryStream, getSignedShort) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getSignedShort(obj->stream_data));
}

PHP_METHOD(BinaryStream, putShort) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putShort(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getLShort) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getLShort(obj->stream_data));
}

PHP_METHOD(BinaryStream, getSignedLShort) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getSignedLShort(obj->stream_data));
}

PHP_METHOD(BinaryStream, putLShort) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putLShort(obj->stream_data, value);
}

// Int operations
PHP_METHOD(BinaryStream, getInt) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getInt(obj->stream_data));
}

PHP_METHOD(BinaryStream, putInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putInt(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getLInt) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getLInt(obj->stream_data));
}

PHP_METHOD(BinaryStream, putLInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putLInt(obj->stream_data, value);
}

// Float operations
PHP_METHOD(BinaryStream, getFloat) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_DOUBLE(BinaryStreamUtils::getFloat(obj->stream_data));
}

PHP_METHOD(BinaryStream, getRoundedFloat) {
    zend_long accuracy;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(accuracy)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_DOUBLE(BinaryStreamUtils::getRoundedFloat(obj->stream_data, static_cast<int>(accuracy)));
}

PHP_METHOD(BinaryStream, putFloat) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putFloat(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getLFloat) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_DOUBLE(BinaryStreamUtils::getLFloat(obj->stream_data));
}

PHP_METHOD(BinaryStream, getRoundedLFloat) {
    zend_long accuracy;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(accuracy)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_DOUBLE(BinaryStreamUtils::getRoundedLFloat(obj->stream_data, static_cast<int>(accuracy)));
}

PHP_METHOD(BinaryStream, putLFloat) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putLFloat(obj->stream_data, value);
}

// Triad operations
PHP_METHOD(BinaryStream, getTriad) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getTriad(obj->stream_data));
}

PHP_METHOD(BinaryStream, putTriad) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putTriad(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getLTriad) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getLTriad(obj->stream_data));
}

PHP_METHOD(BinaryStream, putLTriad) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putLTriad(obj->stream_data, value);
}

// Double operations
PHP_METHOD(BinaryStream, getDouble) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_DOUBLE(BinaryStreamUtils::getDouble(obj->stream_data));
}

PHP_METHOD(BinaryStream, putDouble) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putDouble(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getLDouble) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_DOUBLE(BinaryStreamUtils::getLDouble(obj->stream_data));
}

PHP_METHOD(BinaryStream, putLDouble) {
    double value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putLDouble(obj->stream_data, value);
}

// Long operations
PHP_METHOD(BinaryStream, getLong) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getLong(obj->stream_data));
}

PHP_METHOD(BinaryStream, putLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putLong(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getLLong) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getLLong(obj->stream_data));
}

PHP_METHOD(BinaryStream, putLLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putLLong(obj->stream_data, value);
}

// VarInt operations
PHP_METHOD(BinaryStream, getUnsignedVarInt) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getUnsignedVarInt(obj->stream_data));
}

PHP_METHOD(BinaryStream, putUnsignedVarInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putUnsignedVarInt(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getVarInt) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getVarInt(obj->stream_data));
}

PHP_METHOD(BinaryStream, putVarInt) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putVarInt(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getUnsignedVarLong) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getUnsignedVarLong(obj->stream_data));
}

PHP_METHOD(BinaryStream, putUnsignedVarLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putUnsignedVarLong(obj->stream_data, value);
}

PHP_METHOD(BinaryStream, getVarLong) {
    ZEND_PARSE_PARAMETERS_NONE();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    RETURN_LONG(BinaryStreamUtils::getVarLong(obj->stream_data));
}

PHP_METHOD(BinaryStream, putVarLong) {
    zend_long value;
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    binary_stream_object* obj = Z_BINARY_STREAM_P(ZEND_THIS);
    BinaryStreamUtils::putVarLong(obj->stream_data, value);
}

// Method table for BinaryStream class using generated arginfo
static const zend_function_entry binary_stream_methods[] = {
    PHP_ME(BinaryStream, __construct, arginfo_class_BinaryStream___construct, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, rewind, arginfo_class_BinaryStream_rewind, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, setOffset, arginfo_class_BinaryStream_setOffset, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getOffset, arginfo_class_BinaryStream_getOffset, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getBuffer, arginfo_class_BinaryStream_getBuffer, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, get, arginfo_class_BinaryStream_get, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getRemaining, arginfo_class_BinaryStream_getRemaining, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, put, arginfo_class_BinaryStream_put, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, feof, arginfo_class_BinaryStream_feof, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getBool, arginfo_class_BinaryStream_getBool, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putBool, arginfo_class_BinaryStream_putBool, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getByte, arginfo_class_BinaryStream_getByte, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putByte, arginfo_class_BinaryStream_putByte, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getShort, arginfo_class_BinaryStream_getShort, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getSignedShort, arginfo_class_BinaryStream_getSignedShort, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putShort, arginfo_class_BinaryStream_putShort, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getLShort, arginfo_class_BinaryStream_getLShort, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getSignedLShort, arginfo_class_BinaryStream_getSignedLShort, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putLShort, arginfo_class_BinaryStream_putLShort, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getTriad, arginfo_class_BinaryStream_getTriad, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putTriad, arginfo_class_BinaryStream_putTriad, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getLTriad, arginfo_class_BinaryStream_getLTriad, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putLTriad, arginfo_class_BinaryStream_putLTriad, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getInt, arginfo_class_BinaryStream_getInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putInt, arginfo_class_BinaryStream_putInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getLInt, arginfo_class_BinaryStream_getLInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putLInt, arginfo_class_BinaryStream_putLInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getFloat, arginfo_class_BinaryStream_getFloat, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getRoundedFloat, arginfo_class_BinaryStream_getRoundedFloat, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putFloat, arginfo_class_BinaryStream_putFloat, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getLFloat, arginfo_class_BinaryStream_getLFloat, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getRoundedLFloat, arginfo_class_BinaryStream_getRoundedLFloat, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putLFloat, arginfo_class_BinaryStream_putLFloat, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getDouble, arginfo_class_BinaryStream_getDouble, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putDouble, arginfo_class_BinaryStream_putDouble, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getLDouble, arginfo_class_BinaryStream_getLDouble, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putLDouble, arginfo_class_BinaryStream_putLDouble, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getLong, arginfo_class_BinaryStream_getLong, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putLong, arginfo_class_BinaryStream_putLong, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getLLong, arginfo_class_BinaryStream_getLLong, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putLLong, arginfo_class_BinaryStream_putLLong, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getUnsignedVarInt, arginfo_class_BinaryStream_getUnsignedVarInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putUnsignedVarInt, arginfo_class_BinaryStream_putUnsignedVarInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getVarInt, arginfo_class_BinaryStream_getVarInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putVarInt, arginfo_class_BinaryStream_putVarInt, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getUnsignedVarLong, arginfo_class_BinaryStream_getUnsignedVarLong, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putUnsignedVarLong, arginfo_class_BinaryStream_putUnsignedVarLong, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, getVarLong, arginfo_class_BinaryStream_getVarLong, ZEND_ACC_PUBLIC)
    PHP_ME(BinaryStream, putVarLong, arginfo_class_BinaryStream_putVarLong, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

} // extern "C"

// Object handlers
static zend_object_handlers binary_stream_object_handlers;

static zend_object* binary_stream_create_object(zend_class_entry* ce) {
    binary_stream_object* obj = static_cast<binary_stream_object*>(
        ecalloc(1, sizeof(binary_stream_object) + zend_object_properties_size(ce))
    );

    zend_object_std_init(&obj->std, ce);
    object_properties_init(&obj->std, ce);
    new(&obj->stream_data) BinaryStreamUtils::StreamData();

    obj->std.handlers = &binary_stream_object_handlers;

    return &obj->std;
}

static void binary_stream_free_object(zend_object* object) {
    binary_stream_object* obj = binary_stream_from_obj(object);

    // Destructor for C++ objects
    obj->stream_data.~StreamData();

    zend_object_std_dtor(object);
}

// Class initialization function
extern "C" void init_class_BinaryStream() {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "BinaryStream", binary_stream_methods);
    binary_stream_ce = zend_register_internal_class(&ce);
    binary_stream_ce->create_object = binary_stream_create_object;

    memcpy(&binary_stream_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    binary_stream_object_handlers.offset = XtOffsetOf(binary_stream_object, std);
    binary_stream_object_handlers.free_obj = binary_stream_free_object;
}
