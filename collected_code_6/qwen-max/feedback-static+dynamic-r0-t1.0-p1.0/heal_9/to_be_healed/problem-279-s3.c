#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t decagonal_number(int64_t n) {
    if (n <= 0 || n > (INT64_MAX / 4)) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 133333333333332 * 33333333333333 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:428,execs:237,op:havoc,rep:2)
     */
    int64_t part1 = 4 * n * n;
    if (part1 < 0 || n > (INT64_MAX / 3)) {
        return -1;
    }
    int64_t part2 = 3 * n;
    if (part2 < 0 || part1 < part2) {
        return -1;
    }
    return part1 - part2;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int64_t result = decagonal_number(n);
    if (result == -1) {
        return 1;
    }
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The %lldth decagonal number is: %lld\n", n, result);
    return 0;
}