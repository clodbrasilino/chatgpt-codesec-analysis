#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t centered_hexagonal_number(int64_t n) {
    if (n <= 0 || n > INT64_MAX / 3) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 29999999999999997 * 9999999999999998 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:122,execs:74,op:havoc,rep:2)
     */
    int64_t result = 3 * n * (n - 1) + 1;
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &n) != 1) {
        return 1;
    }
    int64_t result = centered_hexagonal_number(n);
    if (result == -1) {
        printf("Invalid input. The number is too large.\n");
    } else {
        /* Possible weaknesses found:
         *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
         */
        printf("The %lldth centered hexagonal number is: %lld\n", n, result);
    }
    return 0;
}