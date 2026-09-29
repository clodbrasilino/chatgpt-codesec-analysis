#include <stdio.h>
#include <stdlib.h>

long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1625702400 * 11365760000 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:51464,execs:8119,op:havoc,rep:7)
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:34205,execs:6331,op:havoc,rep:9)
             */
            res = (res * x) % p;
        y = y >> 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:51464,execs:8119,op:havoc,rep:7)
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:34205,execs:6331,op:havoc,rep:9)
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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2432902008176640000 * 21 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000000,time:52313,execs:8669,op:havoc,rep:9)
         */
        fact[i] = (fact[i - 1] * i) % p;
    
    long long result = (fact[n] * mod_inverse(fact[r], p)) % p;
    result = (result * mod_inverse(fact[n - r], p)) % p;
    
    free(fact);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:4372,execs:2939,op:havoc,rep:10; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    
    printf("Enter n, r, and p: ");
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid parameters\n");
        return 1;
    }
    
    long long result = ncr_mod_p(n, r, p);
    
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("%lldC%lld mod %lld = %lld\n", n, r, p, result);
    
    return 0;
}