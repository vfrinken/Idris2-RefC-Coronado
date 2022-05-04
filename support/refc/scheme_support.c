#include "scheme_support.h"


Value *scheme_eval(char * expr){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

int64_t scheme_evalOkay(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

Value *scheme_evalResult(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

Value *scheme_debugScheme(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

int64_t scheme_isNumber(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isInteger(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isFloat(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isChar(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isString(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isProcedure(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isSymbol(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isNil(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isPair(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isVector(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int64_t scheme_isBox(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

int scheme_unsafeGetInteger(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

char *scheme_unsafeGetString(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

float scheme_unsafeGetFloat(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

char scheme_unsafeGetChar(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

Value *scheme_unsafeFst(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

Value *scheme_unsafeSnd(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

Value *scheme_unsafeApply(Value *closure, Value * arg){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

Value *scheme_unsafeForce(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

Value *scheme_unsafeVectorRef(Value *vec, int64_t id){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

Value *scheme_unsafeUnbox(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

int scheme_unsafeVectorLength(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return 0;
}

Value *scheme_unsafeVectorToList(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

Value *scheme_makeSymbol(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}

char *scheme_unsafeReadSymbol(Value *v){
    printf("Scheme backend not available in Idris-RefC\n");
    exit(1);
    return NULL;
}
