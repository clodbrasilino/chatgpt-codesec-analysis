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
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -8173347561818554368 + -6366401023241617408 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:6958,execs:4085,op:havoc,rep:2)
             * UBSan: signed integer overflow: 6135418369257504768 + 7011906707722862592 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2311,execs:1490,op:havoc,rep:2)
             */
            res = (res + a) % p;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7011906707722862592 + 7011906707722862592 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:6958,execs:4085,op:havoc,rep:2)
         * UBSan: signed integer overflow: 7387029288794456064 + 7387029288794456064 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2311,execs:1490,op:havoc,rep:2)
         */
        a = (a + a) % p;
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
    
    long long numerator = 1;
    long long denominator = 1;
    
    for (long long i = 0; i < r; i++) {
        numerator = mul_mod(numerator, (n - i) % p, p);
        denominator = mul_mod(denominator, (i + 1) % p, p);
    }
    
    if (denominator == 0)
        return 0;
    
    long long denom_inv = mod_inverse(denominator, p);
    long long result = mul_mod(numerator, denom_inv, p);
    
    return result;
}

int main(void) {
    long long n, r, p;
    
    while (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &n, &r, &p) == 3) {
        if (n < 0 || r < 0 || p <= 1) {
            fprintf(stderr, "Invalid parameters\n");
            continue;
        }
        
        long long result = ncr_mod_p(n, r, p);
        
        printf("%" PRId64 "\n", result);
    }
    
    return 0;
}