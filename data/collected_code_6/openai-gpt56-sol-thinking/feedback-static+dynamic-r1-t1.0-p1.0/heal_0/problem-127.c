#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    bool success;
    int value;
} MultiplicationResult;

static uintmax_t magnitude(int value)
{
    uintmax_t converted = (uintmax_t)value;
    return value < 0 ? UINTMAX_C(0) - converted : converted;
}

static MultiplicationResult multiply_integers(int left, int right)
{
    MultiplicationResult result = { false, 0 };
    bool negative = (left < 0) != (right < 0);
    uintmax_t multiplicand = magnitude(left);
    uintmax_t multiplier = magnitude(right);
    uintmax_t product = 0;
    uintmax_t limit = (uintmax_t)INT_MAX + (negative ? UINTMAX_C(1) : UINTMAX_C(0));

    while (multiplier != 0) {
        if ((multiplier & UINTMAX_C(1)) != 0) {
            if (multiplicand > limit - product) {
                return result;
            }
            product += multiplicand;
        }

        multiplier >>= 1;

        if (multiplier != 0) {
            if (multiplicand > limit - multiplicand) {
                return result;
            }
            multiplicand += multiplicand;
        }
    }

    if (negative) {
        result.value = product == (uintmax_t)INT_MAX + UINTMAX_C(1)
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

    if (scanf("%d %d", &left, &right) != 2) {
        if (fputs("Invalid input\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    MultiplicationResult result = multiply_integers(left, right);

    if (!result.success) {
        if (fputs("Integer overflow\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result.value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}