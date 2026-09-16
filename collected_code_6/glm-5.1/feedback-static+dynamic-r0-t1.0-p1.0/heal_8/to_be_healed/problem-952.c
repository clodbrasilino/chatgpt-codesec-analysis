#include <stdio.h>
#include <stdlib.h>

long long modInverse(long long a, long long p) {
    long long res = 1;
    long long exp = p - 2;
    long long base = a % p;
    base = (base + p) % p;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % p;
        }
        exp = exp / 2;
        base = (base * base) % p;
    }
    return res;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 11, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

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
    long long res = 1;
    long long den = 1;
    for (long long i = 0; i < r; i++) {
        long long num_term = (n - i) % p;
        if (num_term < 0) {
            num_term += p;
        }
        res = (res * num_term) % p;
        
        long long den_term = (i + 1) % p;
        if (den_term < 0) {
            den_term += p;
        }
        den = (den * den_term) % p;
    }
    res = (res * modInverse(den, p)) % p;
    return res;
}

int main(int argc, char const * const * argv) {
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
    if (n < 0 || r < 0) {
        fprintf(stderr, "Error: n and r must be non-negative\n");
        return 1;
    }
    long long result = nCrModP(n, r, p);
    printf("%lld\n", result);
    return 0;
}