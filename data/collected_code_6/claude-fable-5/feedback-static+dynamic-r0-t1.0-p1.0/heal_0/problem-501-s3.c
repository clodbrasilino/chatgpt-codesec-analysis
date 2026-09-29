#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned int gcd(unsigned int a, unsigned int b)
{
    while (b != 0U) {
        unsigned int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static unsigned int safe_abs(int n)
{
    if (n == INT_MIN) {
        return (unsigned int)INT_MAX + 1U;
    }
    if (n < 0) {
        return (unsigned int)(-n);
    }
    return (unsigned int)n;
}

int main(void)
{
    int x = 0;
    int y = 0;

    printf("Enter two integers: ");
    if (scanf("%d %d", &x, &y) != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (x == 0 && y == 0) {
        fprintf(stderr, "Error: GCD of (0, 0) is undefined.\n");
        return EXIT_FAILURE;
    }

    unsigned int result = gcd(safe_abs(x), safe_abs(y));

    if (printf("Greatest common divisor of %d and %d is %u\n", x, y, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}