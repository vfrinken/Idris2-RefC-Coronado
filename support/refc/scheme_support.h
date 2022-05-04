#include "cBackend.h"

Value *scheme_eval(char * expr);

int64_t scheme_evalOkay(Value *v);

Value *scheme_evalResult(Value *v);

Value *scheme_debugScheme(Value *v);

int64_t scheme_isNumber(Value *v);

int64_t scheme_isInteger(Value *v);

int64_t scheme_isFloat(Value *v);

int64_t scheme_isChar(Value *v);

int64_t scheme_isString(Value *v);

int64_t scheme_isProcedure(Value *v);

int64_t scheme_isSymbol(Value *v);

int64_t scheme_isNil(Value *v);

int64_t scheme_isPair(Value *v);

int64_t scheme_isVector(Value *v);

int64_t scheme_isBox(Value *v);

int scheme_unsafeGetInteger(Value *v);

char *scheme_unsafeGetString(Value *v);

float scheme_unsafeGetFloat(Value *v);

char scheme_unsafeGetChar(Value *v);

Value *scheme_unsafeFst(Value *v);

Value *scheme_unsafeSnd(Value *v);

Value *scheme_unsafeApply(Value *closure, Value * arg);

Value *scheme_unsafeForce(Value *v);

Value *scheme_unsafeVectorRef(Value *vec, int64_t id);

Value *scheme_unsafeUnbox(Value *v);

int scheme_unsafeVectorLength(Value *v);

Value *scheme_unsafeVectorToList(Value *v);

Value *scheme_makeSymbol(Value *v);

char *scheme_unsafeReadSymbol(Value *v);
