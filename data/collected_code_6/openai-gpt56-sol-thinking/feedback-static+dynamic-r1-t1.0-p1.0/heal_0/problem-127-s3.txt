#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    bool success;
} MultiplicationResult;

MultiplicationResult multiply_integers(int left, int right)
{
    MultiplicationResult result = {0, true};
    bool negative = (left < 0) != (right < 0);
    unsigned int multiplicand = left < 0
        ? 0u - (unsigned int)left
        : (unsigned int)left;
    unsigned int multiplier = right < 0
        ? 0u - (unsigned int)right
        : (unsigned int)right;
    unsigned int negative_limit = 0u - (unsigned int)INT_MIN;
    unsigned int limit = negative ? negative_limit : (unsigned int)INT_MAX;
    unsigned int product = 0u;

    while (multiplier != 0u) {
        if ((multiplier & 1u) != 0u) {
            if (multiplicand > limit - product) {
                result.success = false;
                return result;
            }
            product += multiplicand;
        }

        multiplier >>= 1u;

        if (multiplier != 0u) {
            if (multiplicand > limit ||
                multiplicand > limit - multiplicand) {
                result.success = false;
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

    return result;
}

int main(void)
{
    int left;
    int right;
    MultiplicationResult result;

    if (scanf("%d%d", &left, &right) != 2) {
        return EXIT_FAILURE;
    }

    result = multiply_integers(left, right);

    if (!result.success) {
        if (fputs("integer overflow\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result.value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}