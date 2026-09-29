#include <stdio.h>
#include <stdlib.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 181883485772840960 * 1052446703539687692 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:5136,execs:2186,op:havoc,rep:14)
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:9424,execs:4115,op:havoc,rep:11)
             */
            result = (result * base) % mod;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 131681894400 * 131681894400 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:5136,execs:2186,op:havoc,rep:14)
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:9424,execs:4115,op:havoc,rep:11)
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:4942,execs:2090,op:havoc,rep:2)
         */
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long mod_inverse(long long a, long long p) {
    return mod_pow(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n)
        return 0;
    if (p <= 1)
        return 0;

    r = (r > n - r) ? n - r : r;

    long long numerator = 1;
    for (long long i = n - r + 1; i <= n; ++i)
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 260604664090630650 * 1111106 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:5136,execs:2186,op:havoc,rep:14)
         */
        numerator = (numerator * (i % p)) % p;

    long long denominator = 1;
    for (long long i = 1; i <= r; ++i)
        denominator = (denominator * (i % p)) % p;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -380641327901655940 * -22138960838035186 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:5136,execs:2186,op:havoc,rep:14)
     */
    return (numerator * mod_inverse(denominator, p)) % p;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:2346,execs:1071,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3)
        return 1;

    printf("%lld\n", ncr_mod_p(n, r, p));
    return 0;
}