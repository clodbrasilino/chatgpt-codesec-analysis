#include <stdio.h>
#include <stdlib.h>

long long int modInverse(long long int a, long long int m) {
    /* Possible weaknesses found:
     *  The scope of the variable 'q' can be reduced. [variableScope]
     *  The scope of the variable 't' can be reduced. [variableScope]
     */
    long long int m0 = m, t, q, x0 = 0, x1 = 1;
    if (m == 1)
        return 0;

    while (a > 1) {
        /* Possible weaknesses found:
         *  Division by zero
         *  Division by zero. [zerodiv]
         */
        q = a / m;
        /* Possible weaknesses found:
         *  Assignment 't=m', assigned value is 13
         */
        t = m;
        /* Possible weaknesses found:
         *  Division by zero. [zerodiv]
         *  Division by zero
         *  Assignment 'm=a%m', assigned value is 0
         */
        m = a % m;
        /* Possible weaknesses found:
         *  Assignment 'a=t', assigned value is 13
         */
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t + q * x0;
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
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 25, got <no output>
  */

long long int nCrModp(long long int n, long long int r, long long int p) {
    if (r > n || r < 0)
        return 0;

    if (r == 0 || r == n)
        return 1;

    long long int fac[n + 1];
    fac[0] = 1;

    for (long long int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    /* Possible weaknesses found:
     *  Calling function 'modInverse', 2nd argument 'p' value is 13
     */
    long long int inv_r = modInverse(fac[r], p);
    long long int inv_n_minus_r = modInverse(fac[n - r], p);

    if (inv_r == 0 || inv_n_minus_r == 0) {
        return 0;
    }

    return (fac[n] * ((inv_r * inv_n_minus_r) % p)) % p;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'p=13', assigned value is 13
     */
    long long int n = 5, r = 2, p = 13;
    /* Possible weaknesses found:
     *  Calling function 'nCrModp', 3rd argument 'p' value is 13
     */
    printf("%lld\n", nCrModp(n, r, p));
    return 0;
}