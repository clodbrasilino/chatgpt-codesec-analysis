#include <stdio.h>
#include <stdlib.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (p == 1) return 0;
    if (r > n - r) r = n - r;

    long long numerator = 1;
    for (long long i = n; i >= n - r + 1; i--) {
        numerator = (numerator * (i % p)) % p;
    }

    long long fact_r = 1;
    for (long long i = 1; i <= r; i++) {
        fact_r = (fact_r * i) % p;
    }

    long long inv_fact_r;
    if (fact_r == 0) {
        inv_fact_r = 0;
    } else {
        inv_fact_r = mod_pow(fact_r, p - 2, p);
    }

    long long result = (numerator * inv_fact_r) % p;

    return result;
}

int main() {
    long long n1 = 5, r1 = 2, p1 = 7;
    long long n2 = 10, r2 = 2, p2 = 13;
    long long n3 = 50, r3 = 25, p3 = 1000000007;

    printf("%lld\n", ncr_mod_p(n1, r1, p1));
    printf("%lld\n", ncr_mod_p(n2, r2, p2));
    printf("%lld\n", ncr_mod_p(n3, r3, p3));

    return 0;
}