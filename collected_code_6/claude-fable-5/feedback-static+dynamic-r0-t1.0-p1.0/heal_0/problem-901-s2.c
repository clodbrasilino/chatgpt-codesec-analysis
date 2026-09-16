#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned long long gcd_ull(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        unsigned long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

static int smallest_multiple(unsigned int n, unsigned long long *result)
{
    unsigned long long lcm = 1ULL;
    unsigned int i;

    if (result == NULL || n == 0U) {
        return -1;
    }

    for (i = 2U; i <= n; i++) {
        unsigned long long g = gcd_ull(lcm, (unsigned long long)i);
        unsigned long long factor = (unsigned long long)i / g;

        if (factor != 0ULL && lcm > ULLONG_MAX / factor) {
            return -1;
        }
        lcm *= factor;
    }

    *result = lcm;
    return 0;
}

int main(void)
{
    unsigned int n = 10U;
    unsigned long long result = 0ULL;

    if (smallest_multiple(n, &result) != 0) {
        if (fprintf(stderr, "Error: cannot compute result for n = %u\n", n) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Smallest multiple of the first %u numbers: %llu\n", n, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}