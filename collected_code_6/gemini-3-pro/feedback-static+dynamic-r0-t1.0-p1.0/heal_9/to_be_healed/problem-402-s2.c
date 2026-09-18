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
 *  expected function body after function declarator
 *  expected parameter declarator
 *  expected declaration specifiers or '...' at end of input
 *  Unmatched '('. Configuration: ''. [syntaxError]
 *  to match this '('
 *  expected ')'
 */
unsigned long long nCrModP_small(