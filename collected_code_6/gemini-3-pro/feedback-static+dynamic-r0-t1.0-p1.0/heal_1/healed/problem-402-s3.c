#include <stdio.h>
#include <stdlib.h>

unsigned long long power(unsigned long long base, unsigned long long exp, unsigned long long p) {
    unsigned long long res = 1;
    base = base % p;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % p;
        }
        exp = exp >> 1;
        base = (base * base) % p;
    }
    return res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    return power(n, p - 2, p);
}

unsigned long long nCrModpDP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (r == 0) return 1;
    if (n < r) return 0;
    
    unsigned long long num = 1;
    unsigned long long den = 1;
    for (unsigned long long i = 1; i <= r; i++) {
        num = (num * (n - i + 1)) % p;
        den = (den * i) % p;
    }
    return (num * modInverse(den, p)) % p;
}

unsigned long long nCrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (r == 0) return 1;
    if (n < r) return 0;
    if (p == 0) return 0;

    unsigned long long res = 1;
    while (n > 0 || r > 0) {
        unsigned long long ni = n % p;
        unsigned long long ri = r % p;
        
        if (ni < ri) {
            return 0;
        }
        
        res = (res * nCrModpDP(ni, ri, p)) % p;
        
        n /= p;
        r /= p;
    }
    
    return res;
}

int main(void) {
    unsigned long long n = 10;
    unsigned long long r = 2;
    unsigned long long p = 13;

    unsigned long long result = nCrModP(n, r, p);
    printf("%llu\n", result);

    return 0;
}