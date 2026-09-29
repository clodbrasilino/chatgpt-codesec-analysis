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

unsigned long long ncrModPFermat(unsigned long long n, int r, int p) {
    if (r == 0)
        return 1;
    unsigned long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;
    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}

int main() {
    int n = 5, r = 2, p = 13;
    printf("Value of nCr %dC%d mod %d is %llu\n", n, r, p, ncrModPFermat(n, r, p));
    return 0;
}