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

    if (n >= p) {
        long long res = 1;
        while (n > 0 || r > 0) {
            long long ni = n % p;
            long long ri = r % p;
            if (ri > ni) return 0;
            if (ri > 0 && ni > 0) {
                long long num = 1;
                for (long long i = ni; i > ni - ri; i--) {
                    num = (num * i) % p;
                }
                long long den = 1;
                for (long long i = 1; i <= ri; i++) {
                    den = (den * i) % p;
                }
                long long inv_den = mod_pow(den, p - 2, p);
                res = (res * num % p) * inv_den % p;
            }
            n /= p;
            r /= p;
        }
        return res;
    }

    long long numerator = 1;
    for (long long i = n; i >= n - r + 1; i--) {
        numerator = (numerator * i) % p;
    }

    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        denominator = (denominator * i) % p;
    }

    long long inv_denominator = mod_pow(denominator, p - 2, p);

    return (numerator * inv_denominator) % p;
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