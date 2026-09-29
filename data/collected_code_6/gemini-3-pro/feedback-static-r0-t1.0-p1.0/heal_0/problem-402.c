#include <stdio.h>

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

long long nCrModP(long long n, long long r, long long p) {
    if (n < r)
        return 0;
    if (r == 0)
        return 1;
    
    long long num = 1;
    long long den = 1;
    
    for (long long i = 0; i < r; i++) {
        num = (num * (n - i)) % p;
        den = (den * (i + 1)) % p;
    }
    
    return (num * modInverse(den, p)) % p;
}

int main() {
    long long n = 10;
    long long r = 2;
    long long p = 13;
    
    if (p <= 0) {
        return 1;
    }
    
    long long result = nCrModP(n, r, p);
    printf("%lld\n", result);
    
    return 0;
}