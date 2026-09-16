#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned int gcd(unsigned int a, unsigned int b);
static unsigned int safe_abs(int n);

static unsigned int safe_abs(int n)
{
    if (n < 0) {
        return (unsigned int)(-(long)n);
    }
    return (unsigned int)n;
}

static unsigned int gcd(unsigned int a, unsigned int b)
{
    if (b == 0U) {
        return a;
    }
    return gcd(b, a % b);
}

int main(void)
{
    int x;
    int y;
    unsigned int result;

    printf("Enter two integers: ");

    if (scanf("%d %d", &x, &y) != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (x == 0 && y == 0) {
        fprintf(stderr, "Error: gcd(0, 0) is undefined.\n");
        return EXIT_FAILURE;
    }

    result = gcd(safe_abs(x), safe_abs(y));

    printf("GCD of %d and %d is %u\n", x, y, result);

    return EXIT_SUCCESS;
}