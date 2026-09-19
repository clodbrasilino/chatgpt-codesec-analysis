#include <stdio.h>
#include <stdlib.h>

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long modInverse(long long n, long long p) {
    return modPow(n, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 0
  */

long long ncrModP(int n, int r, int p) {
    if (r == 0 || r == n)
        return 1;

    long long* fac = (long long*)malloc((n + 1) * sizeof(long long));
    if (fac == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    long long invFacR = modInverse(fac[r], p);
    long long invFacNR = modInverse(fac[n - r], p);

    long long result = (fac[n] * ((invFacR * invFacNR) % p)) % p;
    free(fac);
    return result;
}

int main() {
    int n, r, p;
    printf("Enter the values of n, r, and p: ");
    if (scanf("%d %d %d", &n, &r, &p) != 3) {
        printf("Invalid input\n");
        return 1;
    }

    if (n < 0 || r < 0 || p <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    if (r > n) {
        printf("r should be less than or equal to n\n");
        return 1;
    }

    if (p == 1) {
        printf("Value of C(%d, %d) %d is 0\n", n, r, p);
        return 0;
    }

    long long result = ncrModP(n, r, p);
    if (result < 0)
        result += p;

    printf("Value of C(%d, %d) %d is %lld\n", n, r, p, result);

    return 0;
}