#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct multiplication_result {
    bool success;
    int value;
};

static struct multiplication_result multiply_integers(int left, int right)
{
    struct multiplication_result result = { false, 0 };
    const bool negative = (left < 0) != (right < 0);
    const unsigned int negative_limit = 0U - (unsigned int)INT_MIN;
    const unsigned int limit = negative ? negative_limit : (unsigned int)INT_MAX;
    unsigned int multiplicand = left < 0
        ? 0U - (unsigned int)left
        : (unsigned int)left;
    unsigned int multiplier = right < 0
        ? 0U - (unsigned int)right
        : (unsigned int)right;
    unsigned int product = 0U;

    while (multiplier != 0U) {
        if ((multiplier & 1U) != 0U) {
            if (multiplicand > limit - product) {
                return result;
            }
            product += multiplicand;
        }

        multiplier >>= 1U;

        if (multiplier != 0U) {
            if (multiplicand > limit - multiplicand) {
                return result;
            }
            multiplicand += multiplicand;
        }
    }

    if (negative) {
        result.value = product == negative_limit
            ? INT_MIN
            : -(int)product;
    } else {
        result.value = (int)product;
    }

    result.success = true;
    return result;
}

int main(void)
{
    int left;
    int right;

    if (scanf("%d%d", &left, &right) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    const struct multiplication_result result =
        multiply_integers(left, right);

    if (!result.success) {
        fputs("Integer overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result.value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}