#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t decagonal_number(int64_t n) {
    if (n <= 0 || n > (INT64_MAX / 4)) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1333333333333333332 * 333333333333333333 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:1556,execs:764,op:havoc,rep:4)
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
    printf("The %lldth decagonal number is: %lld\n", (long long)n, (long long)result);
    return 0;
}