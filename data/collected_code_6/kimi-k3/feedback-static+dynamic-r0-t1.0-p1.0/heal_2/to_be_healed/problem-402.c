#include <stdio.h>
#include <stdlib.h>

long long safe_mult(long long a, long long b, long long p) {
    long long res = 0;
    a %= p;
    b %= p;
    while (b > 0) {
        if (b & 1)
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -8754625030724780032 + -1563827425089945600 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000017,time:53707,execs:19236,op:havoc,rep:4)
             */
            res = (res + a) % p;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4865804016353280000 * 2 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000017,time:53707,execs:19236,op:havoc,rep:4)
         */
        a = (a * 2) % p;
        b >>= 1;
    }
    return res;
}

long long power(long long x, unsigned int y, int p) {
    long long res = 1;
    x = x % p;
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