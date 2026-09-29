#include <stdio.h>
#include <stdlib.h>

static unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    return (unsigned long long)(((unsigned __int128)a * (unsigned __int128)b) % (unsigned __int128)m);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 4, got 5
  */

unsigned long long first_factorial_divisible(unsigned long long x)
{
    unsigned long long remainder = 1ULL;
    unsigned long long i;

    if (x == 1ULL) {
        return 1ULL;
    }

    for (i = 1ULL; i <= x; i++) {
        remainder = mulmod(remainder, i, x);
        if (remainder == 0ULL) {
            return i;
        }
    }

    return x;
}

int main(void)
{
    unsigned long long x = 0ULL;
    unsigned long long result;

    printf("Enter a natural number x: ");
    if (scanf("%llu", &x) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (x == 0ULL) {
        fprintf(stderr, "Error: x must be a natural number greater than zero\n");
        return EXIT_FAILURE;
    }

    result = first_factorial_divisible(x);
    printf("The first natural number whose factorial is divisible by %llu is %llu\n", x, result);

    return EXIT_SUCCESS;
}