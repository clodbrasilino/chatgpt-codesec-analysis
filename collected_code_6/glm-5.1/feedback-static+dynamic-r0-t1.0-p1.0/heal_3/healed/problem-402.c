#include <stdio.h>
#include <stdlib.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (p == 1) {
        return 0;
    }
    if (n >= p) {
        return (ncr_mod_p(n / p, r / p, p) * ncr_mod_p(n % p, r % p, p)) % p;
    }
    r = r < (n - r) ? r : (n - r);
    long long res = 1;
    for (long long i = 1; i <= r; i++) {
        res = (res * (n - r + i)) % p;
        res = (res * mod_exp(i, p - 2, p)) % p;
    }
    return res;
}

int main(void) {
    long long n, r, p;
    while (scanf("%lld %lld %lld", &n, &r, &p) == 3) {
        printf("%lld\n", ncr_mod_p(n, r, p));
    }
    return 0;
}