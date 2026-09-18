#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long power(long long x, unsigned long long y, long long p)
{
    long long res = 1;
    
    if (p <= 0) {
        return -1;
    }
    
    x = x % p;
    
    while (y > 0) {
        if (y & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 40320 * 2642908293365760000 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:6646,execs:2758,op:havoc,rep:5)
             * UBSan: signed integer overflow: 65548320768000 * -55316162544774 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:10405,execs:4251,op:havoc,rep:2)
             */
            res = (res * x) % p;
        }
        y = y >> 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2642908293365760000 * 2642908293365760000 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:6646,execs:2758,op:havoc,rep:5)
         * UBSan: signed integer overflow: 19404476731038 * 19404476731038 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:10405,execs:4251,op:havoc,rep:2)
         */
        x = (x * x) % p;
    }
    
    return res;
}

long long modInverse(long long n, long long p)
{
    if (p <= 1) {
        return -1;
    }
    return power(n, p - 2, p);
}

long long nCrModPFermat(long long n, long long r, long long p)
{
    if (p <= 0) {
        return -1;
    }
    
    if (n < 0 || r < 0 || r > n) {
        return 0;
    }
    
    if (r == 0 || r == n) {
        return 1;
    }
    
    if (r > n - r) {
        r = n - r;
    }
    
    long long numerator = 1;
    for (long long i = 0; i < r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7 * 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:1591,execs:692,op:havoc,rep:11)
         */
        numerator = (numerator * (n - i)) % p;
    }
    
    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        denominator = (denominator * i) % p;
    }
    
    long long inv = modInverse(denominator, p);
    if (inv == -1) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 980179200 * -37375090837771 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:10405,execs:4251,op:havoc,rep:2)
     */
    return (numerator * inv) % p;
}

int main(void)
{
    long long n, r, p;
    long long result;
    
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (p <= 0) {
        fprintf(stderr, "Modulus must be positive\n");
        return EXIT_FAILURE;
    }
    
    if (p == 1) {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    
    result = nCrModPFermat(n, r, p);
    
    if (result == -1) {
        fprintf(stderr, "Computation error\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}