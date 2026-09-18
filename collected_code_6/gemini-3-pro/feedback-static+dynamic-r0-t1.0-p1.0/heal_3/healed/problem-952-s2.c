#include <stdio.h>
#include <stdlib.h>

unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p) {
    if (p <= 1) return 0;
    unsigned __int128 res = 1;
    unsigned __int128 base = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * base) % p;
        y = y >> 1;
        base = (base * base) % p;
    }
    return (unsigned long long)res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    if (p <= 1) return 0;
    return power(n, p - 2, p);
}

unsigned long long nCrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (p <= 1)
        return 0;
    if (r > n)
        return 0;
    if (r == 0 || r == n)
        return 1 % p;
    
    if (n >= p) {
        return (unsigned long long)(((unsigned __int128)nCrModP(n / p, r / p, p) * 
                                     (unsigned __int128)nCrModP(n % p, r % p, p)) % p);
    }
    
    if (r > n / 2)
        r = n - r;
        
    unsigned __int128 num = 1;
    unsigned __int128 den = 1;
    
    for (unsigned long long i = 0; i < r; i++) {
        num = (num * (n - i)) % p;
        den = (den * (i + 1)) % p;
    }
    
    return (unsigned long long)((num * modInverse((unsigned long long)den, p)) % p);
}

int main() {
    unsigned long long n, r, p;
    if (scanf("%llu %llu %llu", &n, &r, &p) == 3) {
        printf("%llu\n", nCrModP(n, r, p));
    }
    return 0;
}