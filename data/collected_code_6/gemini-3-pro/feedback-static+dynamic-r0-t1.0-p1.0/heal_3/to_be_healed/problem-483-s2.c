#include <stdio.h>
#include <stdlib.h>

long long get_power(long long n, long long p) {
    long long count = 0;
    while (n > 0) {
        count += n / p;
        n /= p;
    }
    return count;
}

/* Possible weaknesses found:
 *  to match this '{'
 */
long long findFirstFactorialDivisible(long long x) {
    if (x <= 1) {
        return 1;
    }

    long long result = 1;
    long long tempX = x;

    /* Possible weaknesses found:
     *  to match this '{'
     *  Unmatched '{'. Configuration: ''. [syntaxError]
     */
    for (long long p = 2; p * p <= tempX; ++p) {
        /* Possible weaknesses found:
         *  expected expression
         *  expected expression at end of input
         *  expected '}'
         *  expected declaration or statement at end of input
         */
        if (tempX % p ==