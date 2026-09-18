#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t decagonal_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 33333333333 * 33333333333 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:573,execs:315,op:havoc,rep:11)
     */
    if (n > 0 && n * n > INT64_MAX / 4) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 * -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:16689,execs:8090,op:havoc,rep:7)
     * UBSan: signed integer overflow: -88888888808 * -22222222202 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000006,time:24074,execs:11077,op:havoc,rep:1)
     */
    int64_t part1 = 4 * n * n;
    if (n > 0 && n > INT64_MAX / 3) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000005,time:16689,execs:8090,op:havoc,rep:7)
     */
    int64_t part2 = 3 * n;
    if (part1 < 0 || part2 < 0 || part1 < part2) {
        fprintf(stderr, "Overflow detected\n");
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