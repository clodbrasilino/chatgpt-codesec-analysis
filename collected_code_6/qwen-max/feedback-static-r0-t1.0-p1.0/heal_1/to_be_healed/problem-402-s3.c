#include <stdio.h>
#include <stdlib.h>

long long int modInverse(long long int a, long long int m) {
    /* Possible weaknesses found:
     *  The scope of the variable 't' can be reduced. [variableScope]
     *  The scope of the variable 'q' can be reduced. [variableScope]
     */
    long long int m0 = m, t, q;
    long long int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

long long int powerMod(long long int x, long long int y, long long int p) {
    long long int res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

long long int nCrModp(long long int n, long long int r, long long int p) {
    if (r == 0)
        return 1;

    long long int fac[n + 1];
    fac[0] = 1;

    for (long long int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}

int main() {
    long long int n = 5, r = 2, p = 13;
    printf("%lld\n", nCrModp(n, r, p));
    return 0;
}