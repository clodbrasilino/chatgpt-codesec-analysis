#include <stdio.h>
#include <stdlib.h>

unsigned long long power(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    if (mod == 0) return 0;
    unsigned long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (unsigned long long)((__uint128_t)res * base % mod);
        }
        exp = exp >> 1;
        base = (unsigned long long)((__uint128_t)base * base % mod);
    }
    return res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    if (p <= 1) return 0;
    return power(n, p - 2, p);
}

unsigned long long nCrModP_basic(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (p <= 1) return 0;
    if (r == 0) return 1 % p;
    if (n < r) return 0;
    
    if (r > n - r) {
        r = n - r;
    }
    
    unsigned long long num = 1;
    unsigned long long den = 1;
    
    for (unsigned long long i = 0; i < r; i++) {
        num = (unsigned long long)((__uint128_t)num * (n - i) % p);
        den = (unsigned long long)((__uint128_t)den * (i + 1) % p);
    }
    
    return (unsigned long long)((__uint128_t)num * modInverse(den, p) % p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

unsigned long long nCrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (p <= 1) return 0;
    if (r == 0) return 1 % p;
    if (n < r) return 0;
    
    unsigned long long res = 1;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'n>0' is not redundant
     */
    while (n > 0) {
        /* Possible weaknesses found:
         *  Division by zero
         *  Either the condition 'n>0' is redundant or there is division by zero at line 51. [zerodivcond]
         */
        unsigned long long ni = n % p;
        /* Possible weaknesses found:
         *  Division by zero
         *  Either the condition 'n>0' is redundant or there is division by zero at line 52. [zerodivcond]
         */
        unsigned long long ri = r % p;
        
        if (ni < ri) {
            return 0;
        }
        
        res = (unsigned long long)((__uint128_t)res * nCrModP_basic(ni, ri, p) % p);
        
        /* Possible weaknesses found:
         *  Assignment to 'n/=p'
         */
        n /= p;
        r /= p;
    }
    
    return res;
}

int main(void) {
    unsigned long long n, r, p;
    while (scanf("%llu %llu %llu", &n, &r, &p) == 3) {
        printf("%llu\n", nCrModP(n, r, p));
    }
    return EXIT_SUCCESS;
}