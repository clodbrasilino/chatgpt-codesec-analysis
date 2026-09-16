#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned int to_magnitude(int n)
{
    unsigned int result;

    if (n < 0) {
        result = 0U - (unsigned int)n;
    } else {
        result = (unsigned int)n;
    }
    return result;
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
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if ((x == 0) && (y == 0)) {
        fprintf(stderr, "GCD of 0 and 0 is undefined\n");
        return EXIT_FAILURE;
    }

    result = gcd(to_magnitude(x), to_magnitude(y));

    printf("GCD of %d and %d is %u\n", x, y, result);

    return EXIT_SUCCESS;
}