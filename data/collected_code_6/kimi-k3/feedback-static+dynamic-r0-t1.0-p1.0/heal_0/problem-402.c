#include <stdio.h>
#include <stdlib.h>

long long power(long long x, unsigned int y, int p) {
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

long long modInverse(long long n, int p) {
    return power(n, p - 2, p);
}

long long nCrModPFermat(long long n, long long r, long long p) {
    if (r == 0)
        return 1;
    if (r > n)
        return 0;
    if (r > n - r)
        r = n - r;
    
    long long fac[n + 1];
    fac[0] = 1;
    for (long long i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;
    
    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}

int main() {
    long long n, r, p;
    
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid values\n");
        return 1;
    }
    
    printf("%lld\n", nCrModPFermat(n, r, p));
    
    return 0;
}