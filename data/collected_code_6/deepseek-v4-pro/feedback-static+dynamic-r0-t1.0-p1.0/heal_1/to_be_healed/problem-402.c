#include <stdio.h>
#include <stdlib.h>

long long power(long long a, long long b, long long p) {
    long long res = 1;
    a %= p;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % p;
        b >>= 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000015,time:39572,execs:15973,op:havoc,rep:1)
         * UBSan: signed integer overflow: -70609262346240000 * -70609262346240000 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000011,time:35625,execs:14021,op:havoc,rep:3)
         */
        a = (a * a) % p;
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
    r = (r > n - r) ? n - r : r;

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = 0; i < r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 211970764029024000 * 142 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000011,time:35625,execs:14021,op:havoc,rep:3)
         */
        numerator = (numerator * ((n - i) % p)) % p;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2432902008176640000 * 21 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000011,time:35625,execs:14021,op:havoc,rep:3)
         */
        denominator = (denominator * ((i + 1) % p)) % p;
    }

    return (numerator * mod_inverse(denominator, p)) % p;
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