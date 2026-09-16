#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

static unsigned long long addmod(unsigned long long a, unsigned long long b,
                                 unsigned long long m)
{
    if (a >= m - b) {
        return a - (m - b);
    }
    return a + b;
}

static unsigned long long mulmod(unsigned long long a, unsigned long long b,
                                 unsigned long long m)
/* Possible weaknesses found:
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 *  to match this '{'
 */
{
    unsigned long long r = 0;

    /* Possible weaknesses found:
     *  expected '}'
     *  expected declaration or statement at end of input
     */
    a %= m;