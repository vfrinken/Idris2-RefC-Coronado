#include "exportData.h"


void init_Idris2VM(){
    newIORef_Storage(128);
}

void cleanup_idris2VM(){
    if(global_IORef_Storage)
    {
        for(int i=0; i<global_IORef_Storage->filled; i++)
        {
            if(global_IORef_Storage->refs[global_IORef_Storage->filled])
            {
                removeReference(global_IORef_Storage->refs[global_IORef_Storage->filled]);
            }
            free(global_IORef_Storage->refs);
            free(global_IORef_Storage->lock);

        }
    }
}

double extractDouble(Value *v) {
  Value_Double *x = (Value_Double *)v;
  return x->d;
}

char extractChar(Value *v) {
  Value_Char *x = (Value_Char *)v;
  return x->c;
}

uint8_t extractBits8(Value *v) {
  Value_Bits8 *x = (Value_Bits8 *)v;
  return x->ui8;
}

uint16_t extractBits16(Value *v) {
  Value_Bits16 *x = (Value_Bits16 *)v;
  return x->ui16;
}

uint32_t extractBits32(Value *v) {
  Value_Bits32 *x = (Value_Bits32 *)v;
  return x->ui32;
}

uint64_t extractBits64(Value *v) {
  Value_Bits64 *x = (Value_Bits64 *)v;
  return x->ui64;
}

int8_t extractInt8(Value *v) {
  Value_Int8 *x = (Value_Int8 *)v;
  return x->i8;
}

int16_t extractInt16(Value *v) {
  Value_Int16 *x = (Value_Int16 *)v;
  return x->i16;
}

int32_t extractInt32(Value *v) {
  Value_Int32 *x = (Value_Int32 *)v;
  return x->i32;
}

int64_t extractInt64(Value *v) {
  Value_Int64 *x = (Value_Int64 *)v;
  return x->i64;
}

int extractBool(Value *v) {
  Value_Int8 *x = (Value_Int8 *)v;
  return (int)x->i8;
}

char *extractString(Value *v) {
  Value_String *x = (Value_String *)v;
  return x->str;
}

void *extractPointer(Value *v) {
  Value_Pointer *x = (Value_Pointer *)v;
  return x->p;
}

Value_Integer *makeNat(uint64_t n) {
  Value_Integer *retVal = makeInteger();
  mpz_set_ui(retVal->i, n);
  return retVal;
}

uint64_t extractNat(Value *v) { return mpz_get_ui(((Value_Integer *)v)->i); }

enum ValueType getTypeOfValue(Value *v) {
  switch (v->header.tag) {
  case BITS8_TAG:
    return Bits8;
  case BITS16_TAG:
    return Bits16;
  case BITS32_TAG:
    return Bits32;
  case BITS64_TAG:
    return Bits64;
  case INT8_TAG:
    return Int8;
  case INT16_TAG:
    return Int16;
  case INT32_TAG:
    return Int32;
  case INT64_TAG:
    return Int64;
  case INTEGER_TAG:
    return Integer;
  case DOUBLE_TAG:
    return Double;
  case CHAR_TAG:
    return Char;
  case STRING_TAG:
    return String;
  case CLOSURE_TAG:
    return Closure;
  case COMPLETE_CLOSURE_TAG:
    return Closure;
  case POINTER_TAG:
    return Pointer;
  case GC_POINTER_TAG:
    return Pointer;
  default:
    return IdrisInternal;
  }
}
