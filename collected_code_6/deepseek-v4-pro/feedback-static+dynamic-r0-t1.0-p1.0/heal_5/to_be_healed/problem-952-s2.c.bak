#include <stdio.h>
#include <stdlib.h>

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:9010,execs:1281,op:havoc,rep:1)
             * UBSan: signed integer overflow: 2821109907456 * -4659292509279766 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:11825,execs:1599,op:havoc,rep:2)
             */
            res = (res * x) % p;
        y = y >> 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:9010,execs:1281,op:havoc,rep:1)
         */
        x = (x * x) % p;
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
        fact[i] = (fact[i - 1] * (i % p)) % p;
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 39916800 * -906978613372416 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:11825,execs:1599,op:havoc,rep:2)
     */
    long long result = (fact[n] * mod_inverse(fact[r], p)) % p;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2146872239346286 * 3956834445619016 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:11825,execs:1599,op:havoc,rep:2)
     */
    result = (result * mod_inverse(fact[n - r], p)) % p;
    
    free(fact);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:1727,execs:1188,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    
    while (scanf("%lld %lld %lld", &n, &r, &p) == 3) {
        if (n < 0 || r < 0 || p <= 1) {
            fprintf(stderr, "Invalid parameters\n");
            continue;
        }
        
        long long result = ncr_mod_p(n, r, p);
        
        if (result == -1) {
            fprintf(stderr, "Memory allocation failed\n");
            continue;
        }
        
        printf("%lld\n", result);
    }
    
    return 0;
}