#include <stdio.h>
#include <stdlib.h>

unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p) {
    unsigned long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    return power(n, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

unsigned long long nCrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    
    if (n >= p) {
        return (nCrModP(n / p, r / p, p) * nCrModP(n % p, r % p, p)) % p;
    }
    
    if (r > n / 2)
        r = n - r;
        
    unsigned long long num = 1;
    unsigned long long den = 1;
    
    for (unsigned long long i = 0; i < r; i++) {
        num = (num * (n - i)) % p;
        den = (den * (i + 1)) % p;
    }
    
    return (num * modInverse(den, p)) % p;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:93,execs:35,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    unsigned long long n, r, p;
    if (scanf("%llu %llu %llu", &n, &r, &p) == 3) {
        printf("%llu\n", nCrModP(n, r, p));
    }
    return 0;
}