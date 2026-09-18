#include <stdio.h>
#include <stdlib.h>

unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p);
unsigned long long modInverse(unsigned long long n, unsigned long long p);

unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p) {
    if (p <= 1) return 0;
    unsigned __int128 res = 1;
    unsigned __int128 base = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * base) % p;
        y = y >> 1;
        base = (base * base) % p;
    }
    return (unsigned long long)res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    __int128 t = 0;
    __int128 newt = 1;
    __int128 r = p;
    __int128 newr = n;
    
    while (newr != 0) {
        __int128 quotient = r / newr;
        
        __int128 temp_t = t - quotient * newt;
        t = newt;
        newt = temp_t;
        
        __int128 temp_r = r - quotient * newr;
        r = newr;
        newr = temp_r;
    }
    
    if (r > 1) {
        return 0;
    }
    if (t < 0) {
        t = t + p;
    }
    
    return (unsigned long long)t;
}

int main(void) {
    unsigned long long n = 3;
    unsigned long long p = 11;
    unsigned long long inv = modInverse(n, p);
    
    if (inv != 0) {
        printf("%llu\n", inv);
    } else {
        printf("0\n");
    }
    
    return 0;
}