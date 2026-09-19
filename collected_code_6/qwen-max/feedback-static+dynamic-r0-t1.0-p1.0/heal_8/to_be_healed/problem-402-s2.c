#include <stdio.h>
#include <stdlib.h>

unsigned long long modInverse(unsigned long long a, unsigned long long m) {
    unsigned long long m0 = m;
    unsigned long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        unsigned long long q = a / m;
        unsigned long long t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    /* Possible weaknesses found:
     *  Checking if unsigned expression 'x1' is less than zero. [unsignedLessThanZero]
     */
    if (x1 < 0)
        x1 += m0;

    return x1;
}

unsigned long long factorialMod(unsigned long long n, unsigned long long p) {
    unsigned long long result = 1;
    for (unsigned long long i = 1; i <= n; i++)
        result = (result * i) % p;
    return result;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  *  test case 0 failed: expected 6, got 9
  *  test case 1 failed: expected 25, got 23
  */

unsigned long long ncrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (r > n || p <= 1)
        return 0;

    if (n - r < r)
        r = n - r;

    unsigned long long numerator = 1, denominator = 1;

    for (unsigned long long i = 1; i <= r; i++) {
        numerator = (numerator * (n - r + i)) % p;
        denominator = (denominator * i) % p;
    }

    unsigned long long denominatorInv = modInverse(denominator, p);
    if (denominatorInv == 0)
        return 0;

    return (numerator * denominatorInv) % p;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:133,execs:144,op:flip1,pos:6; likely memory-safety defect
  */

int main() {
    unsigned long long n, r, p;
    if (scanf("%llu %llu %llu", &n, &r, &p) != 3) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    printf("%llu\n", ncrModP(n, r, p));
    return 0;
}