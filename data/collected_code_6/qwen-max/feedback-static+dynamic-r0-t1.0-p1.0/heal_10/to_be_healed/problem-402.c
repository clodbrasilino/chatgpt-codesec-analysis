#include <stdio.h>
#include <stdlib.h>

long long modInverse(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        /* Possible weaknesses found:
         *  Division by zero
         *  Division by zero. [zerodiv]
         */
        long long q = a / m;
        /* Possible weaknesses found:
         *  Assignment 't=m', assigned value is 1000000007
         */
        long long t = m;
        /* Possible weaknesses found:
         *  Division by zero. [zerodiv]
         *  Division by zero
         *  Assignment 'm=a%m', assigned value is 0
         */
        m = a % m;
        /* Possible weaknesses found:
         *  Assignment 'a=t', assigned value is 1000000007
         */
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 25, got <no output>
  */

long long ncrModp(long long n, long long r, long long p) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;

    long long fac[n + 1];
    fac[0] = 1;
    for (long long i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    /* Possible weaknesses found:
     *  Calling function 'modInverse', 2nd argument 'p' value is 1000000007
     */
    long long inv_r = modInverse(fac[r], p);
    long long inv_n_r = modInverse(fac[n - r], p);

    return (fac[n] * ((inv_r * inv_n_r) % p)) % p;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'p=1000000007', assigned value is 1000000007
     */
    long long n = 10, r = 3, p = 1000000007;
    /* Possible weaknesses found:
     *  Calling function 'ncrModp', 3rd argument 'p' value is 1000000007
     */
    printf("%lld\n", ncrModp(n, r, p));
    n = 6, r = 3, p = 7;
    printf("%lld\n", ncrModp(n, r, p));
    n = 10, r = 2, p = 13;
    printf("%lld\n", ncrModp(n, r, p));
    n = 5, r = 2, p = 11;
    printf("%lld\n", ncrModp(n, r, p));
    return 0;
}