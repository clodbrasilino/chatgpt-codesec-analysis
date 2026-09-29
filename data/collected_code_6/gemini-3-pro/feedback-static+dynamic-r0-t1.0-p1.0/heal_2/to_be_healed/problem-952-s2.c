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
  *  test case 1 failed: expected 11, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 6, got <no output>
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

int main() {
    unsigned long long n = 10;
    unsigned long long r = 2;
    unsigned long long p = 13;

    unsigned long long result = nCrModP(n, r, p);
    
    printf("Value of nCr %% p is %llu\n", result);

    return 0;
}