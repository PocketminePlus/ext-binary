/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a60bd21ec7256b53c19764c6e0b4bdc57de00c3b */

#include <climits>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wsign-compare"

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_signByte, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Binary_unsignByte arginfo_class_Binary_signByte

#define arginfo_class_Binary_signShort arginfo_class_Binary_signByte

#define arginfo_class_Binary_unsignShort arginfo_class_Binary_signByte

#define arginfo_class_Binary_signInt arginfo_class_Binary_signByte

#define arginfo_class_Binary_unsignInt arginfo_class_Binary_signByte

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_readBool, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_writeBool, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_readByte, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Binary_readSignedByte arginfo_class_Binary_readByte

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_writeByte, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Binary_readShort arginfo_class_Binary_readByte

#define arginfo_class_Binary_readSignedShort arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeShort arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readLShort arginfo_class_Binary_readByte

#define arginfo_class_Binary_readSignedLShort arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeLShort arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readTriad arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeTriad arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readLTriad arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeLTriad arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readInt arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeInt arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readLInt arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeLInt arginfo_class_Binary_writeByte

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_readFloat, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_readRoundedFloat, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, accuracy, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_writeFloat, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Binary_readLFloat arginfo_class_Binary_readFloat

#define arginfo_class_Binary_readRoundedLFloat arginfo_class_Binary_readRoundedFloat

#define arginfo_class_Binary_writeLFloat arginfo_class_Binary_writeFloat

#define arginfo_class_Binary_readDouble arginfo_class_Binary_readFloat

#define arginfo_class_Binary_writeDouble arginfo_class_Binary_writeFloat

#define arginfo_class_Binary_readLDouble arginfo_class_Binary_readFloat

#define arginfo_class_Binary_writeLDouble arginfo_class_Binary_writeFloat

#define arginfo_class_Binary_readLong arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeLong arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readLLong arginfo_class_Binary_readByte

#define arginfo_class_Binary_writeLLong arginfo_class_Binary_writeByte

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_readVarInt, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(1, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Binary_writeVarInt arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readUnsignedVarInt arginfo_class_Binary_readVarInt

#define arginfo_class_Binary_writeUnsignedVarInt arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readVarLong arginfo_class_Binary_readVarInt

#define arginfo_class_Binary_writeVarLong arginfo_class_Binary_writeByte

#define arginfo_class_Binary_readUnsignedVarLong arginfo_class_Binary_readVarInt

#define arginfo_class_Binary_writeUnsignedVarLong arginfo_class_Binary_writeByte

#define arginfo_class_Binary_flipShortEndianness arginfo_class_Binary_signByte

#define arginfo_class_Binary_flipIntEndianness arginfo_class_Binary_signByte

#define arginfo_class_Binary_flipLongEndianness arginfo_class_Binary_signByte

#define arginfo_class_Binary_printFloat arginfo_class_Binary_writeFloat

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Binary_safeUnpack, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_BinaryStream___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, buffer, IS_STRING, 0, "\"\"")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offset, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_rewind, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_setOffset, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_getOffset, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_getBuffer, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_get, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BinaryStream_getRemaining arginfo_class_BinaryStream_getBuffer

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_put, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_feof, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BinaryStream_getBool arginfo_class_BinaryStream_feof

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_putBool, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BinaryStream_getByte arginfo_class_BinaryStream_getOffset

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_putByte, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BinaryStream_getShort arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_getSignedShort arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putShort arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getLShort arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_getSignedLShort arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putLShort arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getTriad arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putTriad arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getLTriad arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putLTriad arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getInt arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putInt arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getLInt arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putLInt arginfo_class_BinaryStream_putByte

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_getFloat, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_getRoundedFloat, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, accuracy, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_BinaryStream_putFloat, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_BinaryStream_getLFloat arginfo_class_BinaryStream_getFloat

#define arginfo_class_BinaryStream_getRoundedLFloat arginfo_class_BinaryStream_getRoundedFloat

#define arginfo_class_BinaryStream_putLFloat arginfo_class_BinaryStream_putFloat

#define arginfo_class_BinaryStream_getDouble arginfo_class_BinaryStream_getFloat

#define arginfo_class_BinaryStream_putDouble arginfo_class_BinaryStream_putFloat

#define arginfo_class_BinaryStream_getLDouble arginfo_class_BinaryStream_getFloat

#define arginfo_class_BinaryStream_putLDouble arginfo_class_BinaryStream_putFloat

#define arginfo_class_BinaryStream_getLong arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putLong arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getLLong arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putLLong arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getUnsignedVarInt arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putUnsignedVarInt arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getVarInt arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putVarInt arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getUnsignedVarLong arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putUnsignedVarLong arginfo_class_BinaryStream_putByte

#define arginfo_class_BinaryStream_getVarLong arginfo_class_BinaryStream_getOffset

#define arginfo_class_BinaryStream_putVarLong arginfo_class_BinaryStream_putByte

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Limits___construct, 0, 0, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Binary, signByte);
ZEND_METHOD(Binary, unsignByte);
ZEND_METHOD(Binary, signShort);
ZEND_METHOD(Binary, unsignShort);
ZEND_METHOD(Binary, signInt);
ZEND_METHOD(Binary, unsignInt);
ZEND_METHOD(Binary, readBool);
ZEND_METHOD(Binary, writeBool);
ZEND_METHOD(Binary, readByte);
ZEND_METHOD(Binary, readSignedByte);
ZEND_METHOD(Binary, writeByte);
ZEND_METHOD(Binary, readShort);
ZEND_METHOD(Binary, readSignedShort);
ZEND_METHOD(Binary, writeShort);
ZEND_METHOD(Binary, readLShort);
ZEND_METHOD(Binary, readSignedLShort);
ZEND_METHOD(Binary, writeLShort);
ZEND_METHOD(Binary, readTriad);
ZEND_METHOD(Binary, writeTriad);
ZEND_METHOD(Binary, readLTriad);
ZEND_METHOD(Binary, writeLTriad);
ZEND_METHOD(Binary, readInt);
ZEND_METHOD(Binary, writeInt);
ZEND_METHOD(Binary, readLInt);
ZEND_METHOD(Binary, writeLInt);
ZEND_METHOD(Binary, readFloat);
ZEND_METHOD(Binary, readRoundedFloat);
ZEND_METHOD(Binary, writeFloat);
ZEND_METHOD(Binary, readLFloat);
ZEND_METHOD(Binary, readRoundedLFloat);
ZEND_METHOD(Binary, writeLFloat);
ZEND_METHOD(Binary, readDouble);
ZEND_METHOD(Binary, writeDouble);
ZEND_METHOD(Binary, readLDouble);
ZEND_METHOD(Binary, writeLDouble);
ZEND_METHOD(Binary, readLong);
ZEND_METHOD(Binary, writeLong);
ZEND_METHOD(Binary, readLLong);
ZEND_METHOD(Binary, writeLLong);
ZEND_METHOD(Binary, readVarInt);
ZEND_METHOD(Binary, writeVarInt);
ZEND_METHOD(Binary, readUnsignedVarInt);
ZEND_METHOD(Binary, writeUnsignedVarInt);
ZEND_METHOD(Binary, readVarLong);
ZEND_METHOD(Binary, writeVarLong);
ZEND_METHOD(Binary, readUnsignedVarLong);
ZEND_METHOD(Binary, writeUnsignedVarLong);
ZEND_METHOD(Binary, flipShortEndianness);
ZEND_METHOD(Binary, flipIntEndianness);
ZEND_METHOD(Binary, flipLongEndianness);
ZEND_METHOD(Binary, printFloat);
ZEND_METHOD(Binary, safeUnpack);
ZEND_METHOD(BinaryStream, __construct);
ZEND_METHOD(BinaryStream, rewind);
ZEND_METHOD(BinaryStream, setOffset);
ZEND_METHOD(BinaryStream, getOffset);
ZEND_METHOD(BinaryStream, getBuffer);
ZEND_METHOD(BinaryStream, get);
ZEND_METHOD(BinaryStream, getRemaining);
ZEND_METHOD(BinaryStream, put);
ZEND_METHOD(BinaryStream, feof);
ZEND_METHOD(BinaryStream, getBool);
ZEND_METHOD(BinaryStream, putBool);
ZEND_METHOD(BinaryStream, getByte);
ZEND_METHOD(BinaryStream, putByte);
ZEND_METHOD(BinaryStream, getShort);
ZEND_METHOD(BinaryStream, getSignedShort);
ZEND_METHOD(BinaryStream, putShort);
ZEND_METHOD(BinaryStream, getLShort);
ZEND_METHOD(BinaryStream, getSignedLShort);
ZEND_METHOD(BinaryStream, putLShort);
ZEND_METHOD(BinaryStream, getTriad);
ZEND_METHOD(BinaryStream, putTriad);
ZEND_METHOD(BinaryStream, getLTriad);
ZEND_METHOD(BinaryStream, putLTriad);
ZEND_METHOD(BinaryStream, getInt);
ZEND_METHOD(BinaryStream, putInt);
ZEND_METHOD(BinaryStream, getLInt);
ZEND_METHOD(BinaryStream, putLInt);
ZEND_METHOD(BinaryStream, getFloat);
ZEND_METHOD(BinaryStream, getRoundedFloat);
ZEND_METHOD(BinaryStream, putFloat);
ZEND_METHOD(BinaryStream, getLFloat);
ZEND_METHOD(BinaryStream, getRoundedLFloat);
ZEND_METHOD(BinaryStream, putLFloat);
ZEND_METHOD(BinaryStream, getDouble);
ZEND_METHOD(BinaryStream, putDouble);
ZEND_METHOD(BinaryStream, getLDouble);
ZEND_METHOD(BinaryStream, putLDouble);
ZEND_METHOD(BinaryStream, getLong);
ZEND_METHOD(BinaryStream, putLong);
ZEND_METHOD(BinaryStream, getLLong);
ZEND_METHOD(BinaryStream, putLLong);
ZEND_METHOD(BinaryStream, getUnsignedVarInt);
ZEND_METHOD(BinaryStream, putUnsignedVarInt);
ZEND_METHOD(BinaryStream, getVarInt);
ZEND_METHOD(BinaryStream, putVarInt);
ZEND_METHOD(BinaryStream, getUnsignedVarLong);
ZEND_METHOD(BinaryStream, putUnsignedVarLong);
ZEND_METHOD(BinaryStream, getVarLong);
ZEND_METHOD(BinaryStream, putVarLong);
ZEND_METHOD(Limits, __construct);


static const zend_function_entry class_BinaryDataException_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_Binary_methods[] = {
	ZEND_ME(Binary, signByte, arginfo_class_Binary_signByte, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, unsignByte, arginfo_class_Binary_unsignByte, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, signShort, arginfo_class_Binary_signShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, unsignShort, arginfo_class_Binary_unsignShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, signInt, arginfo_class_Binary_signInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, unsignInt, arginfo_class_Binary_unsignInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readBool, arginfo_class_Binary_readBool, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeBool, arginfo_class_Binary_writeBool, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readByte, arginfo_class_Binary_readByte, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readSignedByte, arginfo_class_Binary_readSignedByte, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeByte, arginfo_class_Binary_writeByte, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readShort, arginfo_class_Binary_readShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readSignedShort, arginfo_class_Binary_readSignedShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeShort, arginfo_class_Binary_writeShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readLShort, arginfo_class_Binary_readLShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readSignedLShort, arginfo_class_Binary_readSignedLShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeLShort, arginfo_class_Binary_writeLShort, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readTriad, arginfo_class_Binary_readTriad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeTriad, arginfo_class_Binary_writeTriad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readLTriad, arginfo_class_Binary_readLTriad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeLTriad, arginfo_class_Binary_writeLTriad, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readInt, arginfo_class_Binary_readInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeInt, arginfo_class_Binary_writeInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readLInt, arginfo_class_Binary_readLInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeLInt, arginfo_class_Binary_writeLInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readFloat, arginfo_class_Binary_readFloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readRoundedFloat, arginfo_class_Binary_readRoundedFloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeFloat, arginfo_class_Binary_writeFloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readLFloat, arginfo_class_Binary_readLFloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readRoundedLFloat, arginfo_class_Binary_readRoundedLFloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeLFloat, arginfo_class_Binary_writeLFloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readDouble, arginfo_class_Binary_readDouble, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeDouble, arginfo_class_Binary_writeDouble, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readLDouble, arginfo_class_Binary_readLDouble, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeLDouble, arginfo_class_Binary_writeLDouble, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readLong, arginfo_class_Binary_readLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeLong, arginfo_class_Binary_writeLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readLLong, arginfo_class_Binary_readLLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeLLong, arginfo_class_Binary_writeLLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readVarInt, arginfo_class_Binary_readVarInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeVarInt, arginfo_class_Binary_writeVarInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readUnsignedVarInt, arginfo_class_Binary_readUnsignedVarInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeUnsignedVarInt, arginfo_class_Binary_writeUnsignedVarInt, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readVarLong, arginfo_class_Binary_readVarLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeVarLong, arginfo_class_Binary_writeVarLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, readUnsignedVarLong, arginfo_class_Binary_readUnsignedVarLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, writeUnsignedVarLong, arginfo_class_Binary_writeUnsignedVarLong, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, flipShortEndianness, arginfo_class_Binary_flipShortEndianness, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, flipIntEndianness, arginfo_class_Binary_flipIntEndianness, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, flipLongEndianness, arginfo_class_Binary_flipLongEndianness, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, printFloat, arginfo_class_Binary_printFloat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Binary, safeUnpack, arginfo_class_Binary_safeUnpack, ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	ZEND_FE_END
};


static const zend_function_entry class_BinaryStream_methods[] = {
	ZEND_ME(BinaryStream, __construct, arginfo_class_BinaryStream___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, rewind, arginfo_class_BinaryStream_rewind, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, setOffset, arginfo_class_BinaryStream_setOffset, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getOffset, arginfo_class_BinaryStream_getOffset, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getBuffer, arginfo_class_BinaryStream_getBuffer, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, get, arginfo_class_BinaryStream_get, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getRemaining, arginfo_class_BinaryStream_getRemaining, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, put, arginfo_class_BinaryStream_put, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, feof, arginfo_class_BinaryStream_feof, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getBool, arginfo_class_BinaryStream_getBool, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putBool, arginfo_class_BinaryStream_putBool, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getByte, arginfo_class_BinaryStream_getByte, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putByte, arginfo_class_BinaryStream_putByte, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getShort, arginfo_class_BinaryStream_getShort, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getSignedShort, arginfo_class_BinaryStream_getSignedShort, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putShort, arginfo_class_BinaryStream_putShort, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getLShort, arginfo_class_BinaryStream_getLShort, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getSignedLShort, arginfo_class_BinaryStream_getSignedLShort, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putLShort, arginfo_class_BinaryStream_putLShort, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getTriad, arginfo_class_BinaryStream_getTriad, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putTriad, arginfo_class_BinaryStream_putTriad, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getLTriad, arginfo_class_BinaryStream_getLTriad, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putLTriad, arginfo_class_BinaryStream_putLTriad, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getInt, arginfo_class_BinaryStream_getInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putInt, arginfo_class_BinaryStream_putInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getLInt, arginfo_class_BinaryStream_getLInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putLInt, arginfo_class_BinaryStream_putLInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getFloat, arginfo_class_BinaryStream_getFloat, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getRoundedFloat, arginfo_class_BinaryStream_getRoundedFloat, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putFloat, arginfo_class_BinaryStream_putFloat, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getLFloat, arginfo_class_BinaryStream_getLFloat, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getRoundedLFloat, arginfo_class_BinaryStream_getRoundedLFloat, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putLFloat, arginfo_class_BinaryStream_putLFloat, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getDouble, arginfo_class_BinaryStream_getDouble, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putDouble, arginfo_class_BinaryStream_putDouble, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getLDouble, arginfo_class_BinaryStream_getLDouble, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putLDouble, arginfo_class_BinaryStream_putLDouble, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getLong, arginfo_class_BinaryStream_getLong, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putLong, arginfo_class_BinaryStream_putLong, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getLLong, arginfo_class_BinaryStream_getLLong, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putLLong, arginfo_class_BinaryStream_putLLong, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getUnsignedVarInt, arginfo_class_BinaryStream_getUnsignedVarInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putUnsignedVarInt, arginfo_class_BinaryStream_putUnsignedVarInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getVarInt, arginfo_class_BinaryStream_getVarInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putVarInt, arginfo_class_BinaryStream_putVarInt, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getUnsignedVarLong, arginfo_class_BinaryStream_getUnsignedVarLong, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putUnsignedVarLong, arginfo_class_BinaryStream_putUnsignedVarLong, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, getVarLong, arginfo_class_BinaryStream_getVarLong, ZEND_ACC_PUBLIC)
	ZEND_ME(BinaryStream, putVarLong, arginfo_class_BinaryStream_putVarLong, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Limits_methods[] = {
	ZEND_ME(Limits, __construct, arginfo_class_Limits___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};

static zend_class_entry *register_class_BinaryDataException(zend_class_entry *class_entry_Exception)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "BinaryDataException", class_BinaryDataException_methods);
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Exception);
	class_entry->ce_flags |= ZEND_ACC_NO_DYNAMIC_PROPERTIES;

	return class_entry;
}

static zend_class_entry *register_class_Binary(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Binary", class_Binary_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;

	return class_entry;
}

static zend_class_entry *register_class_BinaryStream(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "BinaryStream", class_BinaryStream_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_NO_DYNAMIC_PROPERTIES;

	return class_entry;
}

static zend_class_entry *register_class_Limits(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Limits", class_Limits_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;

	zval const_UINT8_MAX_value;
	ZVAL_LONG(&const_UINT8_MAX_value, 0xff);
	zend_string *const_UINT8_MAX_name = zend_string_init_interned("UINT8_MAX", sizeof("UINT8_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_UINT8_MAX_name, &const_UINT8_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_UINT8_MAX_name);
	ZEND_ASSERT(0xff == 255);

	zval const_INT8_MIN_value;
	ZVAL_LONG(&const_INT8_MIN_value, -0x7f - 1);
	zend_string *const_INT8_MIN_name = zend_string_init_interned("INT8_MIN", sizeof("INT8_MIN") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT8_MIN_name, &const_INT8_MIN_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT8_MIN_name);
	ZEND_ASSERT(-0x7f - 1 == -128);

	zval const_INT8_MAX_value;
	ZVAL_LONG(&const_INT8_MAX_value, 0x7f);
	zend_string *const_INT8_MAX_name = zend_string_init_interned("INT8_MAX", sizeof("INT8_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT8_MAX_name, &const_INT8_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT8_MAX_name);
	ZEND_ASSERT(0x7f == 127);

	zval const_UINT16_MAX_value;
	ZVAL_LONG(&const_UINT16_MAX_value, 0xffff);
	zend_string *const_UINT16_MAX_name = zend_string_init_interned("UINT16_MAX", sizeof("UINT16_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_UINT16_MAX_name, &const_UINT16_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_UINT16_MAX_name);
	ZEND_ASSERT(0xffff == 65535);

	zval const_INT16_MIN_value;
	ZVAL_LONG(&const_INT16_MIN_value, -0x7fff - 1);
	zend_string *const_INT16_MIN_name = zend_string_init_interned("INT16_MIN", sizeof("INT16_MIN") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT16_MIN_name, &const_INT16_MIN_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT16_MIN_name);
	ZEND_ASSERT(-0x7fff - 1 == -32768);

	zval const_INT16_MAX_value;
	ZVAL_LONG(&const_INT16_MAX_value, 0x7fff);
	zend_string *const_INT16_MAX_name = zend_string_init_interned("INT16_MAX", sizeof("INT16_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT16_MAX_name, &const_INT16_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT16_MAX_name);
	ZEND_ASSERT(0x7fff == 32767);

	zval const_UINT32_MAX_value;
	ZVAL_LONG(&const_UINT32_MAX_value, 0xffffffff);
	zend_string *const_UINT32_MAX_name = zend_string_init_interned("UINT32_MAX", sizeof("UINT32_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_UINT32_MAX_name, &const_UINT32_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_UINT32_MAX_name);
	ZEND_ASSERT(0xffffffff == 4294967295);

	zval const_INT32_MIN_value;
	ZVAL_LONG(&const_INT32_MIN_value, -0x7fffffff - 1);
	zend_string *const_INT32_MIN_name = zend_string_init_interned("INT32_MIN", sizeof("INT32_MIN") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT32_MIN_name, &const_INT32_MIN_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT32_MIN_name);
	ZEND_ASSERT(-0x7fffffff - 1 == -2147483648);

	zval const_INT32_MAX_value;
	ZVAL_LONG(&const_INT32_MAX_value, 0x7fffffff);
	zend_string *const_INT32_MAX_name = zend_string_init_interned("INT32_MAX", sizeof("INT32_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT32_MAX_name, &const_INT32_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT32_MAX_name);
	ZEND_ASSERT(0x7fffffff == 2147483647);

	zval const_UINT64_MAX_value;
	ZVAL_DOUBLE(&const_UINT64_MAX_value, (double)0xffffffffffffffffULL);
	zend_string *const_UINT64_MAX_name = zend_string_init_interned("UINT64_MAX", sizeof("UINT64_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_UINT64_MAX_name, &const_UINT64_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_UINT64_MAX_name);
	ZEND_ASSERT((double)0xffffffffffffffffULL == 1.8446744073709552E+19);

	zval const_INT64_MIN_value;
	ZVAL_LONG(&const_INT64_MIN_value, -0x7fffffffffffffff - 1);
	zend_string *const_INT64_MIN_name = zend_string_init_interned("INT64_MIN", sizeof("INT64_MIN") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT64_MIN_name, &const_INT64_MIN_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT64_MIN_name);
	ZEND_ASSERT(-0x7fffffffffffffff - 1 == LLONG_MIN);

	zval const_INT64_MAX_value;
	ZVAL_LONG(&const_INT64_MAX_value, 0x7fffffffffffffff);
	zend_string *const_INT64_MAX_name = zend_string_init_interned("INT64_MAX", sizeof("INT64_MAX") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_INT64_MAX_name, &const_INT64_MAX_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_INT64_MAX_name);
	ZEND_ASSERT(0x7fffffffffffffff == 9223372036854775807);

	return class_entry;
}

#pragma GCC diagnostic pop