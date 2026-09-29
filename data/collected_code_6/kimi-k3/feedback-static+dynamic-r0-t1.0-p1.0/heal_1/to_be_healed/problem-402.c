#include <stdio.h>
#include <stdlib.h>

long long power(long long x, unsigned int y, int p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

long long modInverse(long long n, int p) {
    return power(n, p - 2, p);
}

long long nCrModPFermat(long long n, long long r, long long p) {
    if (r == 0)
        return 1;
    if (r > n)
        return 0;
    if (r > n - r)
        r = n - r;
    
    long long fac[n + 1];
    fac[0] = 1;
    for (long long i = 1; i <= n; i++)
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 122169992087943869 * 86 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:19771,execs:7819,op:havoc,rep:12)
         */
        fac[i] = (fac[i - 1] * i) % p;
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 118297725350832374 * 1669262522 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:19771,execs:7819,op:havoc,rep:12)
     * UBSan: signed integer overflow: 2278422091411200 * 604040068 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:10172,execs:3932,op:havoc,rep:1)
     * UBSan: signed integer overflow: -55071459188201683 * 1592387321 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:19771,execs:7819,op:havoc,rep:12)
     */
    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:3144,execs:1234,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    long long n, r, p;
    
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid values\n");
        return 1;
    }
    
    printf("%lld\n", nCrModPFermat(n, r, p));
    
    return 0;
}