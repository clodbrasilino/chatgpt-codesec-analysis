#include <stdio.h>
#include <stdlib.h>

static unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    return (unsigned long long)(((unsigned __int128)a * (unsigned __int128)b) % (unsigned __int128)m);
}

unsigned long long first_factorial_divisible(unsigned long long x)
/* Possible weaknesses found:
 *  to match this '{'
 */
{
    unsigned long long remainder;
    unsigned long long i;

    /* Possible weaknesses found:
     *  to match this '{'
     *  expected declaration or statement at end of input
     *  Unmatched '{'. Configuration: ''. [syntaxError]
     *  expected '}'
     */
    if (x == 1ULL) {