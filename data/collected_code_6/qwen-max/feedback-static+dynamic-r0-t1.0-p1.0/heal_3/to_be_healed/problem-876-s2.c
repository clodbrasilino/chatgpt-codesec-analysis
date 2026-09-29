#include <stdio.h>
#include <stdint.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int64_t lcm(int64_t a, int64_t b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * 6 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:263,execs:136,op:havoc,rep:1)
     */
    return (a / gcd(a, b)) * b;
}

int main() {
    int64_t x, y;
    printf("Enter two positive integers: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld %lld", &x, &y) == 2) {
        if (x > 0 && y > 0) {
            /* Possible weaknesses found:
             *  %lld in format string (no. 3) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
             *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
             *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
             */
            printf("LCM of %lld and %lld is %lld\n", x, y, lcm(x, y));
        } else {
            printf("Please enter positive integers.\n");
        }
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}