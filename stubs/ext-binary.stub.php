<?php

/** @generate-class-entries */

/**
 * Exception thrown when binary data operations fail
 * 
 * @strict-properties
 */
class BinaryDataException extends Exception
{
}

final class Binary
{
    // Sign/unsign operations
    public static function signByte(int $value): int {}
    public static function unsignByte(int $value): int {}
    public static function signShort(int $value): int {}
    public static function unsignShort(int $value): int {}
    public static function signInt(int $value): int {}
    public static function unsignInt(int $value): int {}

    // Boolean operations
    public static function readBool(string $data): bool {}
    public static function writeBool(bool $value): string {}

    // Byte operations
    public static function readByte(string $data): int {}
    public static function readSignedByte(string $data): int {}
    public static function writeByte(int $value): string {}

    // Short operations (big-endian)
    public static function readShort(string $data): int {}
    public static function readSignedShort(string $data): int {}
    public static function writeShort(int $value): string {}

    // Short operations (little-endian)
    public static function readLShort(string $data): int {}
    public static function readSignedLShort(string $data): int {}
    public static function writeLShort(int $value): string {}

    // Triad operations (3-byte, big-endian)
    public static function readTriad(string $data): int {}
    public static function writeTriad(int $value): string {}

    // Triad operations (3-byte, little-endian)
    public static function readLTriad(string $data): int {}
    public static function writeLTriad(int $value): string {}

    // Int operations (big-endian)
    public static function readInt(string $data): int {}
    public static function writeInt(int $value): string {}

    // Int operations (little-endian)
    public static function readLInt(string $data): int {}
    public static function writeLInt(int $value): string {}

    // Float operations (big-endian)
    public static function readFloat(string $data): float {}
    public static function readRoundedFloat(string $data, int $accuracy): float {}
    public static function writeFloat(float $value): string {}

    // Float operations (little-endian)
    public static function readLFloat(string $data): float {}
    public static function readRoundedLFloat(string $data, int $accuracy): float {}
    public static function writeLFloat(float $value): string {}

    // Double operations (big-endian)
    public static function readDouble(string $data): float {}
    public static function writeDouble(float $value): string {}

    // Double operations (little-endian)
    public static function readLDouble(string $data): float {}
    public static function writeLDouble(float $value): string {}

    // Long operations (big-endian)
    public static function readLong(string $data): int {}
    public static function writeLong(int $value): string {}

    // Long operations (little-endian)
    public static function readLLong(string $data): int {}
    public static function writeLLong(int $value): string {}

    // Variable-length integer operations
    public static function readVarInt(string $buffer, int &$offset): int {}
    public static function writeVarInt(int $value): string {}
    public static function readUnsignedVarInt(string $buffer, int &$offset): int {}
    public static function writeUnsignedVarInt(int $value): string {}

    // Variable-length long operations
    public static function readVarLong(string $buffer, int &$offset): int {}
    public static function writeVarLong(int $value): string {}
    public static function readUnsignedVarLong(string $buffer, int &$offset): int {}
    public static function writeUnsignedVarLong(int $value): string {}

    // Utility operations
    public static function flipShortEndianness(int $value): int {}
    public static function flipIntEndianness(int $value): int {}
    public static function flipLongEndianness(int $value): int {}

    // String formatting
    public static function printFloat(float $value): string {}

    // Safe unpacking operation
    private static function safeUnpack(string $format, string $data): string {}
}

/**
 * Stream-based binary data reader/writer
 * 
 * Provides an object-oriented interface for reading and writing binary data
 * with automatic offset management.
 * 
 * @strict-properties
 */
class BinaryStream
{
    public function __construct(string $buffer = "", int $offset = 0) {}

    // Stream management
    public function rewind(): void {}
    public function setOffset(int $offset): void {}
    public function getOffset(): int {}
    public function getBuffer(): string {}
    public function get(int $length): string {}
    public function getRemaining(): string {}
    public function put(string $data): void {}
    public function feof(): bool {}

    // Boolean operations
    public function getBool(): bool {}
    public function putBool(bool $value): void {}

    // Byte operations
    public function getByte(): int {}
    public function putByte(int $value): void {}

    // Short operations (big-endian)
    public function getShort(): int {}
    public function getSignedShort(): int {}
    public function putShort(int $value): void {}

    // Short operations (little-endian)
    public function getLShort(): int {}
    public function getSignedLShort(): int {}
    public function putLShort(int $value): void {}

    // Triad operations (3-byte, big-endian)
    public function getTriad(): int {}
    public function putTriad(int $value): void {}

    // Triad operations (3-byte, little-endian)
    public function getLTriad(): int {}
    public function putLTriad(int $value): void {}

    // Int operations (big-endian)
    public function getInt(): int {}
    public function putInt(int $value): void {}

    // Int operations (little-endian)
    public function getLInt(): int {}
    public function putLInt(int $value): void {}

    // Float operations (big-endian)
    public function getFloat(): float {}
    public function getRoundedFloat(int $accuracy): float {}
    public function putFloat(float $value): void {}

    // Float operations (little-endian)
    public function getLFloat(): float {}
    public function getRoundedLFloat(int $accuracy): float {}
    public function putLFloat(float $value): void {}

    // Double operations (big-endian)
    public function getDouble(): float {}
    public function putDouble(float $value): void {}

    // Double operations (little-endian)
    public function getLDouble(): float {}
    public function putLDouble(float $value): void {}

    // Long operations (big-endian)
    public function getLong(): int {}
    public function putLong(int $value): void {}

    // Long operations (little-endian)
    public function getLLong(): int {}
    public function putLLong(int $value): void {}

    // Variable-length integer operations
    public function getUnsignedVarInt(): int {}
    public function putUnsignedVarInt(int $value): void {}
    public function getVarInt(): int {}
    public function putVarInt(int $value): void {}

    // Variable-length long operations
    public function getUnsignedVarLong(): int {}
    public function putUnsignedVarLong(int $value): void {}
    public function getVarLong(): int {}
    public function putVarLong(int $value): void {}
}

/**
 * Integer limit constants
 * 
 * Provides constants for various integer type limits used in binary operations.
 * 
 * @strict-properties
 * @not-serializable
 */
final class Limits
{
    /**
     * @var int
     * @cvalue 0xff
     */
    public const UINT8_MAX = 255;

    /**
     * @var int
     * @cvalue -0x7f - 1
     */
    public const INT8_MIN = -128;

    /**
     * @var int
     * @cvalue 0x7f
     */
    public const INT8_MAX = 127;

    /**
     * @var int
     * @cvalue 0xffff
     */
    public const UINT16_MAX = 65535;

    /**
     * @var int
     * @cvalue -0x7fff - 1
     */
    public const INT16_MIN = -32768;

    /**
     * @var int
     * @cvalue 0x7fff
     */
    public const INT16_MAX = 32767;

    /**
     * @var int
     * @cvalue 0xffffffff
     */
    public const UINT32_MAX = 4294967295;

    /**
     * @var int
     * @cvalue -0x7fffffff - 1
     */
    public const INT32_MIN = -2147483648;

    /**
     * @var int
     * @cvalue 0x7fffffff
     */
    public const INT32_MAX = 2147483647;

    /**
     * @var float
     * @cvalue (double)0xffffffffffffffffULL
     */
    public const UINT64_MAX = 1.8446744073709552E+19;

    /**
     * @var int
     * @cvalue -0x7fffffffffffffff - 1
     */
    public const INT64_MIN = -9223372036854775808;

    /**
     * @var int
     * @cvalue 0x7fffffffffffffff
     */
    public const INT64_MAX = 9223372036854775807;

    private function __construct() {}
}
