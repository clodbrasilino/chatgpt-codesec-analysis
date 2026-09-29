#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static long long mul_mod(long long a, long long b, long long p) {
    long long res = 0;
    a %= p;
    if (a < 0) a += p;
    b %= p;
    if (b < 0) b += p;
    while (b > 0) {
        if (b & 1) {
            res = (res + a);
            if (res >= p) res -= p;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4611686018427387904 + 4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:483,execs:335,op:havoc,rep:1)
         */
        a = (a + a);
        if (a >= p) a -= p;
        b >>= 1;
    }
    return res;
}

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    if (x < 0) x += p;
    while (y > 0) {
        if (y & 1)
            res = mul_mod(res, x, p);
        y = y >> 1;
        x = mul_mod(x, x, p);
    }
    return res;
}

long long mod_inverse(long long n, long long p) {
    return power(n, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    if (n - r < r)
        r = n - r;
    
    long long *fact = (long long *)malloc((r + 1) * sizeof(long long));
    if (fact == NULL)
        return -1;
    
    fact[0] = 1;
    for (long long i = 1; i <= r; i++) {
        long long term = (n - r + i) % p;
        fact[i] = mul_mod(fact[i - 1], term, p);
    }
    
    long long numerator = fact[r];
    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        denominator = mul_mod(denominator, i % p, p);
    }
    
    long long result = mul_mod(numerator, mod_inverse(denominator, p), p);
    
    free(fact);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:45937,execs:26100,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    
    while (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &n, &r, &p) == 3) {
        if (n < 0 || r < 0 || p <= 1) {
            fprintf(stderr, "Invalid parameters\n");
            continue;
        }
        
        long long result = ncr_mod_p(n, r, p);
        
        if (result == -1) {
            fprintf(stderr, "Memory allocation failed\n");
            continue;
        }
        
        printf("%" PRId64 "\n", result);
    }
    
    return 0;
}