#include<stdio.h>
#include<stdlib.h>

#include "refc001.h"


// Value *makeNat(uint64_t n)
// {
//     Value_Integer *retVal = makeInteger();
//     mpz_set_ui(retVal->i, n);
//     return (Value*)retVal;
// }
//
// uint64_t extractNat(Value* v)
// {
//     return mpz_get_ui(((Value_Integer*)v)->i);
// }

int main(){

    Value * a =(Value*)makeInt8(4);
    Value * b = (Value*)makePointer(NULL);
    execFct(a, b);
    removeReference(a);
    removeReference(b);


    Value * c = (Value*)makeNat(128);
    Value * d = (Value*)makeNat(7);
    Value * e = addTwoNumbers(c, d);

    printf("c = %i\n", (int)extractNat(c));
    printf("d = %i\n", (int)extractNat(d));
    printf("e = %i\n", (int)extractNat(e));
    removeReference(c);
    removeReference(d);
    removeReference(e);

}
