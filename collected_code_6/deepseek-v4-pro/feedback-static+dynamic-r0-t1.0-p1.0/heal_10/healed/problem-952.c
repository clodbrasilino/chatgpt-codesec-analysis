#include <stdio.h>
#include <stdlib.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long mod_inverse(long long a, long long mod) {
    long long m0 = mod, y = 0, x = 1;
    if (mod <= 1) return 0;
    a %= mod;
    if (a < 0) a += mod;
    if (a == 0) return 0;
    while (a > 1) {
        long long q = a / mod;
        long long t = mod;
        mod = a % mod;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
        if (mod == 0) return 0;
    }
    if (x < 0) x += m0;
    return x;
}

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (r > n - r) {
        r = n - r;
    }

    if (p <= 1) {
        return 0;
    }

    long long *fact = (long long *)malloc(p * sizeof(long long));
    if (fact == NULL) {
        return 0;
    }

    fact[0] = 1;
    for (long long i = 1; i < p; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }

    long long result = 1;
    while (n > 0 || r > 0) {
        long long ni = n % p;
        long long ri = r % p;
        if (ri > ni) {
            free(fact);
            return 0;
        }
        if (ri == 0 || ri == ni) {
            n /= p;
            r /= p;
            continue;
        }
        long long inv1 = mod_inverse(fact[ri], p);
        long long inv2 = mod_inverse(fact[(ni - ri) % p], p);
        if ((inv1 == 0 && fact[ri] != 0) || (inv2 == 0 && fact[(ni - ri) % p] != 0)) {
            free(fact);
            return 0;
        }
        result = (result * fact[ni]) % p;
        result = (result * inv1) % p;
        result = (result * inv2) % p;
        n /= p;
        r /= p;
    }

    free(fact);
    return result;
}

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        return 1;
    }
    if (p <= 1) {
        return 1;
    }
    printf("%lld\n", ncr_mod_p(n, r, p));
    return 0;
}