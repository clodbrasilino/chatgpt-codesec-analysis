#include <stdio.h>
#include <stdlib.h>

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

/* Possible weaknesses found:
 *  expected function body after function declarator
 *  to match this '('
 *  Unmatched '('. Configuration: ''. [syntaxError]
 *  expected ')'
 */
unsigned long long modInverse(unsigned long long n, unsigned long