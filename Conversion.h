#pragma once
#include <stdint.h>

const char* ToString(uint64_t Value);
const char* ToString(int64_t Value);
const char* ToString(uint32_t Value);
const char* ToString(int32_t Value);
const char* ToString(uint16_t Value);
const char* ToString(int16_t Value);
const char* ToString(uint8_t Value);
const char* ToString(int8_t Value);
const char* ToHexString(uint64_t Value);
const char* ToHexString(int64_t Value);
const char* ToHexString(uint32_t Value);
const char* ToHexString(int32_t Value);
const char* ToHexString(uint16_t Value);
const char* ToHexString(int16_t Value);
const char* ToHexString(uint8_t Value);
const char* ToHexString(int8_t Value);
const char* ToString(double Value, uint8_t DecimalPlaces);
const char* ToString(double Value);
const char* ToString(float Value, uint8_t DecimalPlaces);
const char* ToString(float Value);