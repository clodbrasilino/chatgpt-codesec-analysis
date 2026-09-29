#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

static int power(double a, int b, double *result)
{
    double res = 1.0;
    double base = a;
    unsigned int exp;

    if (result == NULL) {
        return -1;
    }

    if (a == 0.0 && b < 0) {
        return -1;
    }

    if (b < 0) {
        if (b == INT_MIN) {
            exp = (unsigned int)INT_MAX + 1U;
        } else {
            exp = (unsigned int)(-b);
        }
        base = 1.0 / a;
    } else {
        exp = (unsigned int)b;
    }

    while (exp > 0U) {
        if ((exp & 1U) == 1U) {
            res *= base;
        }
        base *= base;
        exp >>= 1U;
    }

    if (isinf(res) || isnan(res)) {
        return -1;
    }

    *result = res;
    return 0;
}

int main(void)
{
    double a = 0.0;
    int b = 0;
    double result = 0.0;

    printf("Enter base (a): ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent (b): ");
    if (scanf("%d", &b) != 1) {
        fprintf(stderr, "Invalid input for exponent\n");
        return EXIT_FAILURE;
    }

    if (power(a, b, &result) != 0) {
        fprintf(stderr, "Computation error: invalid operation or overflow\n");
        return EXIT_FAILURE;
    }

    printf("%g^%d = %g\n", a, b, result);
    return EXIT_SUCCESS;
}