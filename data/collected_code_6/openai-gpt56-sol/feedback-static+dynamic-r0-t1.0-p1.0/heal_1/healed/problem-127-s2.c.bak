#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int multiply_int32(int32_t lhs, int32_t rhs, int32_t *result)
{
    int64_t product;

    if (result == NULL) {
        return 0;
    }

    product = (int64_t)lhs * (int64_t)rhs;

    if (product < INT32_MIN || product > INT32_MAX) {
        return 0;
    }

    *result = (int32_t)product;
    return 1;
}

int main(void)
{
    int32_t lhs;
    int32_t rhs;
    int32_t result;

    if (scanf("%" SCNd32 " %" SCNd32, &lhs, &rhs) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!multiply_int32(lhs, rhs, &result)) {
        fputs("Multiplication overflow\n", stderr);
        return 1;
    }

    printf("%" PRId32 "\n", result);
    return 0;
}