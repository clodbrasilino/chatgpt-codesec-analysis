#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

long long mul_mod(long long a, long long b, long long p)
{
    if (p <= 0) {
        return -1;
    }
    
    if (p <= LLONG_MAX / 2) {
        unsigned long long ua = (unsigned long long)(a % p);
        unsigned long long ub = (unsigned long long)(b % p);
        if (a < 0) ua = (ua + (unsigned long long)p) % (unsigned long long)p;
        if (b < 0) ub = (ub + (unsigned long long)p) % (unsigned long long)p;
        return (long long)((ua * ub) % (unsigned long long)p);
    }
    
    unsigned long long res = 0;
    unsigned long long ua = (unsigned long long)(a % p);
    unsigned long long ub = (unsigned long long)(b % p);
    unsigned long long up = (unsigned long long)p;
    
    if (a < 0) ua = (ua + up) % up;
    if (b < 0) ub = (ub + up) % up;
    
    while (ub > 0) {
        if (ub & 1) {
            res = (res + ua) % up;
        }
        ua = (ua + ua) % up;
        ub >>= 1;
    }
    
    return (long long)res;
}

long long power(long long x, unsigned long long y, long long p)
{
    if (p <= 0) {
        return -1;
    }
    
    long long res = 1;
    x = x % p;
    if (x < 0) {
        x += p;
    }
    
    while (y > 0) {
        if (y & 1) {
            res = mul_mod(res, x, p);
            if (res == -1) {
                return -1;
            }
        }
        y = y >> 1;
        if (y > 0) {
            x = mul_mod(x, x, p);
            if (x == -1) {
                return -1;
            }
        }
    }
    
    return res;
}

long long modInverse(long long n, long long p)
{
    if (p <= 1) {
        return -1;
    }
    return power(n, (unsigned long long)(p - 2), p);
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
        long long term = (n - i) % p;
        if (term < 0) {
            term += p;
        }
        numerator = mul_mod(numerator, term, p);
        if (numerator == -1) {
            return -1;
        }
    }
    
    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        long long term = i % p;
        if (term < 0) {
            term += p;
        }
        denominator = mul_mod(denominator, term, p);
        if (denominator == -1) {
            return -1;
        }
    }
    
    long long inv = modInverse(denominator, p);
    if (inv == -1) {
        return -1;
    }
    
    long long result = mul_mod(numerator, inv, p);
    if (result == -1) {
        return -1;
    }
    
    return result;
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