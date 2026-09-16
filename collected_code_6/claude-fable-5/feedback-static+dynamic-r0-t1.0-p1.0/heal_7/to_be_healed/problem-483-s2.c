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
    unsigned long long remainder;
    unsigned long long i;

    if (x == 1ULL) {
        return 1ULL;
    }

    remainder = 1ULL;
    for (i = 2ULL; ; i++) {
        remainder = mulmod(remainder, i, x);
        if (remainder == 0ULL) {
            return i;
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    unsigned long long x;

    if (argc > 1) {
        x = strtoull(argv[1], NULL, 10);
    } else {
        if (scanf("%llu", &x) != 1) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    if (x == 0ULL) {
        fprintf(stderr, "Input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", first_factorial_divisible(x));

    return EXIT_SUCCESS;
}