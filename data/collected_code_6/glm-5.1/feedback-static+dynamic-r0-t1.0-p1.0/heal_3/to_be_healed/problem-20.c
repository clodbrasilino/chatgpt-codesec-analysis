#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }

    for (unsigned long long k = 1; k <= sizeof(unsigned long long) * CHAR_BIT; k++) {
        /* Possible weaknesses found:
         * UBSan: shift exponent 64 is too large for 64-bit type 'unsigned long long' (AFL crash: id:000000,sig:06,src:000000,time:437,execs:479,op:havoc,rep:2)
         *  Assignment 'power=1ULL<<k', assigned value is greater than 0
         */
        unsigned long long power = 1ULL << k;

        /* Possible weaknesses found:
         *  Condition 'power==0' is always false
         *  Condition 'power==0' is always false [knownConditionTrueFalse]
         */
        if (k > 1 && power == 0) {
            return false;
        }

        unsigned long long term = k * (power - 1);

        if (term == n) {
            return true;
        }

        if (term > n) {
            return false;
        }
    }

    return false;
}

int main(void) {
    unsigned long long num;

    if (scanf("%llu", &num) != 1) {
        return 1;
    }

    if (is_woodall(num)) {
        printf("True\n");
    } else {
        printf("0\n");
    }

    return 0;
}