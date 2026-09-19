#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t mul_mod(int64_t a, int64_t b, int64_t mod) {
    int64_t result = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 8913082594685902248 + 1034571992370200576 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000028,time:38718,execs:17093,op:havoc,rep:7)
             * UBSan: signed integer overflow: -8173347561818554368 + -6366401023241617408 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000000,time:16997,execs:7366,op:havoc,rep:14)
             */
            result = (result + a) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7011906707722862592 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000000,time:16997,execs:7366,op:havoc,rep:14)
         * UBSan: signed integer overflow: 4611686018427387904 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:5156,execs:2182,op:havoc,rep:6)
         * UBSan: signed integer overflow: 4870329016519938048 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000028,time:38718,execs:17093,op:havoc,rep:7)
         */
        a = (a * 2) % mod;
        b >>= 1;
    }
    return result;
}

int64_t power_mod(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

int64_t mod_inverse(int64_t a, int64_t p) {
    return power_mod(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 11, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int64_t ncr_mod_p(int64_t n, int64_t r, int64_t p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -8 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000023,time:47575,execs:20086,op:havoc,rep:3)
     */
    if (r > n - r) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -8 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000023,time:47575,execs:20086,op:havoc,rep:3)
         */
        r = n - r;
    }

    int64_t numerator = 1;
    int64_t denominator = 1;

    for (int64_t i = 0; i < r; i++) {
        numerator = mul_mod(numerator, (n - i) % p, p);
        denominator = mul_mod(denominator, (i + 1) % p, p);
    }

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}

int main(void) {
    int64_t n, r, p;

    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     *  %lld in format string (no. 2) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     *  %lld in format string (no. 3) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        return 1;
    }

    if (p <= 1) {
        return 1;
    }

    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("%lld\n", ncr_mod_p(n, r, p));

    return 0;
}