#include <stdio.h>
#include <stdlib.h>

long long mul_mod(long long a, long long b, long long p) {
    long long res = 0;
    a %= p;
    b %= p;
    if (a < 0) a += p;
    if (b < 0) b += p;
    while (b > 0) {
        if (b & 1)
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -4773477407050405246 + -8736854443376508928 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000023,time:41936,execs:16987,op:havoc,rep:2)
             * UBSan: signed integer overflow: 3294464004646478649 + 8539818392200282112 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000025,time:27463,execs:13523,op:havoc,rep:7)
             */
            res = (res + a) % p;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4611686018427387904 + 4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000025,time:27463,execs:13523,op:havoc,rep:7)
         * UBSan: signed integer overflow: 5825422222219018240 + 5825422222219018240 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000023,time:41936,execs:16987,op:havoc,rep:2)
         */
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

long long power(long long a, long long b, long long p) {
    long long res = 1;
    a %= p;
    if (a < 0) a += p;
    while (b > 0) {
        if (b & 1)
            res = mul_mod(res, a, p);
        b >>= 1;
        a = mul_mod(a, a, p);
    }
    return res;
}

long long mod_inverse(long long n, long long p) {
    return power(n, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    if (r > n - r)
        r = n - r;

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = 0; i < r; i++) {
        numerator = mul_mod(numerator, (n - i) % p, p);
        denominator = mul_mod(denominator, (i + 1) % p, p);
    }

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (p <= 1) {
        fprintf(stderr, "p must be a prime number greater than 1\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", ncr_mod_p(n, r, p));
    return EXIT_SUCCESS;
}