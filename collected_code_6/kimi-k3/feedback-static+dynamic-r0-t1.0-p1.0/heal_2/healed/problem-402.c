#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long safe_mult(long long a, long long b, long long p) {
    if (p <= 0) return 0;
    if (a < 0) a += p;
    if (b < 0) b += p;
    
    unsigned long long ua = (unsigned long long)a;
    unsigned long long ub = (unsigned long long)b;
    unsigned long long up = (unsigned long long)p;
    unsigned long long res = 0;
    
    while (ub > 0) {
        if (ub & 1)
            res = (res + ua) % up;
        ua = (ua * 2) % up;
        ub >>= 1;
    }
    return (long long)res;
}

long long power(long long x, unsigned int y, int p) {
    long long res = 1;
    x = x % p;
    if (x < 0) x += p;
    while (y > 0) {
        if (y & 1)
            res = safe_mult(res, x, p);
        y = y >> 1;
        x = safe_mult(x, x, p);
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
    
    if (n > 1000000) {
        fprintf(stderr, "Input too large\n");
        exit(1);
    }
    
    long long *fac = malloc((n + 1) * sizeof(long long));
    if (!fac) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    fac[0] = 1;
    for (long long i = 1; i <= n; i++)
        fac[i] = safe_mult(fac[i - 1], i, p);
    
    long long result = safe_mult(safe_mult(fac[n], modInverse(fac[r], p), p), 
                                 modInverse(fac[n - r], p), p);
    
    free(fac);
    return result;
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