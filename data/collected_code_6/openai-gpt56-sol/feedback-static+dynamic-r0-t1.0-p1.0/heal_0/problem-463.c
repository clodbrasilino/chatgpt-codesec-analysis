#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

static bool multiply_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((a > 0 && b > 0 && a > INT64_MAX / b) ||
        (a > 0 && b < 0 && b < INT64_MIN / a) ||
        (a < 0 && b > 0 && a < INT64_MIN / b) ||
        (a < 0 && b < 0 && a < INT64_MAX / b)) {
        return false;
    }

    *result = a * b;
    return true;
}

static bool maximum_product_subarray(const int64_t array[], size_t length,
                                     int64_t *maximum_product)
{
    if (array == NULL || maximum_product == NULL || length == 0U) {
        return false;
    }

    int64_t current_maximum = array[0];
    int64_t current_minimum = array[0];
    int64_t best = array[0];

    for (size_t i = 1U; i < length; ++i) {
        int64_t product_with_maximum;
        int64_t product_with_minimum;

        if (!multiply_int64(current_maximum, array[i], &product_with_maximum) ||
            !multiply_int64(current_minimum, array[i], &product_with_minimum)) {
            return false;
        }

        int64_t next_maximum = array[i];
        int64_t next_minimum = array[i];

        if (product_with_maximum > next_maximum) {
            next_maximum = product_with_maximum;
        }
        if (product_with_minimum > next_maximum) {
            next_maximum = product_with_minimum;
        }
        if (product_with_maximum < next_minimum) {
            next_minimum = product_with_maximum;
        }
        if (product_with_minimum < next_minimum) {
            next_minimum = product_with_minimum;
        }

        current_maximum = next_maximum;
        current_minimum = next_minimum;

        if (current_maximum > best) {
            best = current_maximum;
        }
    }

    *maximum_product = best;
    return true;
}

int main(void)
{
    const int64_t array[] = {2, 3, -2, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int64_t result;

    if (!maximum_product_subarray(array, length, &result)) {
        fputs("Unable to calculate the maximum product.\n", stderr);
        return 1;
    }

    if (printf("Maximum product: %" PRId64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}