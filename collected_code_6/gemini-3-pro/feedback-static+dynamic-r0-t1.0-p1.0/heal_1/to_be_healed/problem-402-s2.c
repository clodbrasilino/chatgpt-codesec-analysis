#include <stdio.h>
#include <stdlib.h>

unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p) {
    unsigned long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    return power(n, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

unsigned long long nCrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (n < r)
        return 0;
    if (r == 0)
        return 1;

    unsigned long long* fac = (unsigned long long*)malloc((n + 1) * sizeof(unsigned long long));
    if (fac == NULL) {
        return 0; 
    }

    fac[0] = 1;
    for (unsigned long long i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    unsigned long long res = (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
    free(fac);
    return res;
}

int main() {
    unsigned long long n = 10;
    unsigned long long r = 2;
    unsigned long long p = 13;

    unsigned long long result = nCrModP(n, r, p);
    printf("%llu\n", result);

    return 0;
}