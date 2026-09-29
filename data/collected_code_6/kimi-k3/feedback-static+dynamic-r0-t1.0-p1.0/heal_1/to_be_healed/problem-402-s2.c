#include <stdio.h>
#include <stdlib.h>

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:5672,execs:2369,op:havoc,rep:6)
         */
        x = (x * x) % p;
    }
    return res;
}

long long modInverse(long long n, long long p) {
    return power(n, p - 2, p);
}

long long nCrModPFermat(long long n, long long r, long long p) {
    if (n < r)
        return 0;
    if (n == r)
        return 1;
    if (r > n - r)
        r = n - r;
    
    long long numerator = 1;
    for (long long i = 0; i < r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7 * 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:3142,execs:1299,op:havoc,rep:2)
         */
        numerator = (numerator * (n - i)) % p;
    }
    
    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        denominator = (denominator * i) % p;
    }
    
    return (numerator * modInverse(denominator, p)) % p;
}

int main(void) {
    long long n, r, p;
    
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid parameters\n");
        return EXIT_FAILURE;
    }
    
    long long result = nCrModPFermat(n, r, p);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}