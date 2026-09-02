#include <stdio.h>
#include <stdlib.h>

long long modInverse(long long a, long long m) {
    /* Possible weaknesses found:
     *  The scope of the variable 't' can be reduced. [variableScope]
     *  The scope of the variable 'q' can be reduced. [variableScope]
     */
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

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

long long ncrModp(long long n, long long r, long long p) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;

    long long fac[n + 1];
    fac[0] = 1;
    for (long long i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}

int main() {
    long long n = 10, r = 3, p = 1000000007;
    printf("%lld\n", ncrModp(n, r, p));
    return 0;
}