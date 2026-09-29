#include <stdio.h>
#include <stdlib.h>

long long modInverse(long long a, long long p) {
    long long res = 1;
    long long exp = p - 2;
    long long base = a % p;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % p;
        }
        exp = exp / 2;
        base = (base * base) % p;
    }
    return res;
}

long long nCrModP(long long n, long long r, long long p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1 % p;
    }
    if (r > n - r) {
        r = n - r;
    }
    long long numerator = 1;
    long long denominator = 1;
    for (long long i = 0; i < r; i++) {
        numerator = (numerator * (n - i)) % p;
        denominator = (denominator * (i + 1)) % p;
    }
    return (numerator * modInverse(denominator, p)) % p;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n> <r> <p>\n", argv[0]);
        return 1;
    }
    long long n = strtoll(argv[1], NULL, 10);
    long long r = strtoll(argv[2], NULL, 10);
    long long p = strtoll(argv[3], NULL, 10);
    if (p <= 1) {
        fprintf(stderr, "Error: p must be a prime greater than 1\n");
        return 1;
    }
    long long result = nCrModP(n, r, p);
    printf("%lld\n", result);
    return 0;
}