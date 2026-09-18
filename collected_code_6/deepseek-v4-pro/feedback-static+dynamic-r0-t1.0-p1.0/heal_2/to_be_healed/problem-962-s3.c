#include <stdio.h>
#include <stdint.h>

int64_t sum_even_in_range(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (l % 2 != 0) {
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    int64_t n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 34 + 9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000006,time:3271,execs:1989,op:havoc,rep:3)
     * UBSan: signed integer overflow: 2222222222220549945 * 4444444444447788776 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000004,time:2842,execs:1719,op:havoc,rep:13)
     * UBSan: signed integer overflow: 4611686018427387887 * -9223372036854775776 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000006,time:3271,execs:1989,op:havoc,rep:3)
     */
    return n * (l + r) / 2;
}

int main(void) {
    int64_t l, r;
    printf("Enter lower bound: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &l) != 1) {
        return 1;
    }
    printf("Enter upper bound: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &r) != 1) {
        return 1;
    }
    int64_t result = sum_even_in_range(l, r);
    /* Possible weaknesses found:
     *  %lld in format string (no. 3) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("Sum of even numbers in range [%lld, %lld]: %lld\n", l, r, result);
    return 0;
}