#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got -9223372036854775793
  *  test case 0 failed: expected 14, got -9223372036854775798
  *  test case 1 failed: expected 14, got -9223372036854775796
  */

long setLeftMostUnsetBit(long n) {
    long result = n;
    bool found = false;
    /* Possible weaknesses found:
     *  Assignment 'i=63', assigned value is 63
     */
    for (int i = 63; i >= 0; --i) {
        /* Possible weaknesses found:
         * UBSan: left shift of 1 by 63 places cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:113,execs:122,op:havoc,rep:6)
         *  Shifting signed 64-bit value by 63 bits is implementation-defined behaviour [shiftTooManyBitsSigned]
         *  Shift
         */
        if (!(n & ((1L << i)))) {
            /* Possible weaknesses found:
             * UBSan: left shift of 1 by 63 places cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:113,execs:122,op:havoc,rep:6)
             */
            result |= (1L << i);
            found = true;
            break;
        }
    }
    return found ? result : -1;
}

int main() {
    long n;
    printf("Enter a number: ");
    if (scanf("%ld", &n) == 1) {
        long newNumber = setLeftMostUnsetBit(n);
        if (newNumber != -1) {
            /* Possible weaknesses found:
             *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
             */
            printf("New number with the leftmost unset bit set: %lld\n", newNumber);
        } else {
            printf("All bits are set.\n");
        }
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}