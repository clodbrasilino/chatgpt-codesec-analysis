#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static long long mul_mod(long long a, long long b, long long p) {
    long long res = 0;
    a %= p;
    b %= p;
    while (b > 0) {
        if (b & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -8173347561818554368 + -6366401023241617408 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:9396,execs:1243,op:havoc,rep:2)
             */
            res = (res + a) % p;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4611686018427387904 + 4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:47058,execs:6779,op:havoc,rep:8)
         * UBSan: signed integer overflow: 7011906707722862592 + 7011906707722862592 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:9396,execs:1243,op:havoc,rep:2)
         */
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
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
  *  test case 1 failed: expected 11, got 0
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    if (n - r < r)
        r = n - r;
    
    long long *fact = (long long *)malloc((n + 1) * sizeof(long long));
    if (fact == NULL)
        return -1;
    
    fact[0] = 1;
    for (long long i = 1; i <= n; i++)
        fact[i] = mul_mod(fact[i - 1], i % p, p);
    
    long long result = mul_mod(fact[n], mod_inverse(fact[r], p), p);
    result = mul_mod(result, mod_inverse(fact[n - r], p), p);
    
    free(fact);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:9018,execs:997,op:havoc,rep:9; likely memory-safety defect
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