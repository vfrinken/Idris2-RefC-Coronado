#pragma once

#include "cBackend.h"

void init_Idris2VM();
void cleanup_idris2VM();

Value_Integer *makeNat(uint64_t n);

double extractDouble(Value *);
char extractChar(Value *);
uint8_t extractBits8(Value *);
uint16_t extractBits16(Value *);
uint32_t extractBits32(Value *);
uint64_t extractBits64(Value *);
int8_t extractInt8(Value *);
int16_t extractInt16(Value *);
int32_t extractInt32(Value *);
int64_t extractInt64(Value *);
int extractBool(Value *);
char *extractString(Value *);
void *extractPointer(Value *);
uint64_t extractNat(Value *v);

enum ValueType {
  Bits8,
  Bits16,
  Bits32,
  Bits64,
  Int8,
  Int16,
  Int32,
  Int64,
  Integer,
  Double,
  Char,
  String,
  Closure,
  Pointer,
  IdrisInternal
};

enum ValueType getTypeOfValue(Value *);
