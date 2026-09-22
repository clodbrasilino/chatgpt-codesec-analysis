#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

static bool multiply(int a, int b, int *result)
{
    unsigned int ua;
    unsigned int ub;
    unsigned int product;
    bool negative;

    if (result == NULL) {
        return false;
    }

    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }

    negative = (a < 0) != (b < 0);

    if (a < 0) {
        ua = (unsigned int)(-(a + 1)) + 1u;
    } else {
        ua = (unsigned int)a;
    }

    if (b < 0) {
        ub = (unsigned int)(-(b + 1)) + 1u;
    } else {
        ub = (unsigned int)b;
    }

    product = 0u;

    while (ub > 0u) {
        if ((ub & 1u) != 0u) {
            if (product > UINT_MAX - ua) {
                return false;
            }
            product += ua;
        }
        ub >>= 1;
        if (ub > 0u) {
            if (ua > UINT_MAX >> 1) {
                return false;
            }
            ua <<= 1;
        }
    }

    if (negative) {
        if (product > (unsigned int)INT_MAX + 1u) {
            return false;
        }
        if (product == (unsigned int)INT_MAX + 1u) {
            *result = INT_MIN;
        } else {
            *result = -(int)product;
        }
    } else {
        if (product > (unsigned int)INT_MAX) {
            return false;
        }
        *result = (int)product;
    }

    return true;
}

int main(void)
{
    int x = 12;
    int y = -7;
    int result = 0;

    if (multiply(x, y, &result)) {
        if (printf("%d * %d = %d\n", x, y, result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Multiplication overflow detected\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    x = INT_MAX;
    y = 2;

    if (multiply(x, y, &result)) {
        if (printf("%d * %d = %d\n", x, y, result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Multiplication overflow detected\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}