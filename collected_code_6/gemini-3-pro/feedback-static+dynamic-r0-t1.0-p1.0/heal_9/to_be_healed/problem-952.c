#include <stdio.h>

unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p) {
    if (p <= 1) return 0;
    unsigned long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (unsigned long long)((unsigned __int128)res * x % p);
        y >>= 1;
        x = (unsigned long long)((unsigned __int128)x * x % p);
    }
    return res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    if (p <= 1) return 0;
    return power(n, p - 2, p);
}

unsigned long long nCrModP_small(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (p <= 1 || r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    if (r > n - r)
        r = n - r;

    unsigned long long num = 1, den = 1;
    for (unsigned long long i = 0; i < r; i++) {
        num = (unsigned long long)((unsigned __int128)num * (n - i) % p);
        den = (unsigned long long)((unsigned __int128)den * (i + 1) % p);
    }
    return (unsigned long long)((unsigned __int128)num * modInverse(den, p) % p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

unsigned long long nCrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (p <= 1)
        return 0;
    if (r > n)
        return 0;
    if (r == 0 || n == r)
        return 1;

    unsigned long long res = 1;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'n>0' is not redundant
     */
    while (n > 0) {
        /* Possible weaknesses found:
         *  Division by zero
         *  Either the condition 'n>0' is redundant or there is division by zero at line 48. [zerodivcond]
         */
        unsigned long long ni = n % p;
        /* Possible weaknesses found:
         *  Division by zero
         *  Either the condition 'n>0' is redundant or there is division by zero at line 49. [zerodivcond]
         */
        unsigned long long ri = r % p;
        if (ri > ni)
            return 0;
        res = (unsigned long long)((unsigned __int128)res * nCrModP_small(ni, ri, p) % p);
        /* Possible weaknesses found:
         *  Assignment to 'n/=p'
         */
        n /= p;
        r /= p;
    }
    return res;
}

int main(void) {
    unsigned long long n, r, p;
    if (scanf("%llu %llu %llu", &n, &r, &p) == 3) {
        unsigned long long result = nCrModP(n, r, p);
        printf("%llu\n", result);
    }
    return 0;
}