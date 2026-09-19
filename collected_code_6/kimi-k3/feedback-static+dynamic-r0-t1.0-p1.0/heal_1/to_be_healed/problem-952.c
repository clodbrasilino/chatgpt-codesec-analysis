#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 7776 * -44863756222365292 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:6686,execs:2342,op:havoc,rep:3)
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:4959,execs:1741,op:havoc,rep:1)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:4959,execs:1741,op:havoc,rep:1)
         */
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

long long modInverse(long long n, long long p) {
    return power(n, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

long long nCrModP(long long n, long long r, long long p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    
    long long numerator = 1;
    for (long long i = 0; i < r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7 * 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2346,execs:857,op:havoc,rep:1)
         */
        numerator = (numerator * (n - i)) % p;
    }
    
    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        denominator = (denominator * i) % p;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 990 * 69811868777125307 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:6686,execs:2342,op:havoc,rep:3)
     */
    long long result = (numerator * modInverse(denominator, p)) % p;
    return result;
}

int main(void) {
    long long n, r, p;
    
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || r < 0 || p <= 0) {
        fprintf(stderr, "Invalid parameters\n");
        return EXIT_FAILURE;
    }
    
    if (r > n) {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    
    long long result = nCrModP(n, r, p);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}