#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

long long modInverse(long long n, long long p) {
    return power(n, p - 2, p);
}

long long nCrModP(long long n, long long r, long long p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (r > n - r) {
        r = n - r;
    }
    
    if (n >= p) {
        long long result = 1;
        while (n > 0 || r > 0) {
            long long ni = n % p;
            long long ri = r % p;
            if (ri > ni) {
                return 0;
            }
            
            long long numerator = 1;
            for (long long i = 0; i < ri; i++) {
                numerator = (numerator * (ni - i)) % p;
            }
            
            long long denominator = 1;
            for (long long i = 1; i <= ri; i++) {
                denominator = (denominator * i) % p;
            }
            
            result = (result * numerator % p) * modInverse(denominator, p) % p;
            n /= p;
            r /= p;
        }
        return result;
    }
    
    long long numerator = 1;
    for (long long i = 0; i < r; i++) {
        numerator = (numerator * (n - i)) % p;
    }
    
    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        denominator = (denominator * i) % p;
    }
    
    long long result = (numerator * modInverse(denominator, p)) % p;
    return result;
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
    
    if (r > n) {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    
    long long result = nCrModP(n, r, p);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}