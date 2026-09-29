#include <stdio.h>
#include <stdint.h>

int64_t decagonal_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 13333333332 * 3333333333 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:290,execs:146,op:havoc,rep:1)
     * UBSan: signed integer overflow: -4 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:719,execs:325,op:havoc,rep:6)
     * UBSan: signed integer overflow: 4 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:719,execs:325,op:havoc,rep:6)
     */
    int64_t part1 = 4 * n * n;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:719,execs:325,op:havoc,rep:6)
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
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The %lldth decagonal number is: %lld\n", n, result);
    return 0;
}