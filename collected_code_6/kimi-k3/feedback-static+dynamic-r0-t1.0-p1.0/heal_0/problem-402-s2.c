#include <stdio.h>
#include <stdlib.h>

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
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