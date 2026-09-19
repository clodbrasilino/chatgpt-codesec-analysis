#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_overflow(long a, long b) {
    if (b > 0 && a > LONG_MAX - b) return true;
    if (b < 0 && a < LONG_MIN - b) return true;
    return false;
}

long derangement(long n) {
    long a = 1, b = 0;
    for (long i = 0; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:301,execs:133,op:havoc,rep:2)
         */
        long temp = (i + 1) * (a + b);
        /* Possible weaknesses found:
         *  Calling function 'is_overflow' returns 0
         *  Condition 'is_overflow(temp,0)' is always false
         *  Condition 'is_overflow(temp,0)' is always false [knownConditionTrueFalse]
         */
        if (is_overflow(a, b) || is_overflow(b, temp) || is_overflow(temp, 0)) return -1;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) return 1;
    if (n < 0) return 1;
    long result = derangement(n);
    if (result == -1) {
        printf("Computation overflowed.\n");
    } else {
        printf("The %ld-th derangement number is: %ld\n", n, result);
    }
    return 0;
}