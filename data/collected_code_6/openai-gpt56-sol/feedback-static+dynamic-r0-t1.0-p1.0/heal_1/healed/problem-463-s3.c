#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((a > 0 && b > 0 && a > INT64_MAX / b) ||
        (a > 0 && b < 0 && b < INT64_MIN / a) ||
        (a < 0 && b > 0 && a < INT64_MIN / b) ||
        (a < 0 && b < 0 && a < INT64_MAX / b)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int maximum_product_subarray(const int64_t *array, size_t length,
                                    int64_t *maximum_product)
{
    if (array == NULL || maximum_product == NULL || length == 0U) {
        return 0;
    }

    int64_t maximum_ending = array[0];
    int64_t minimum_ending = array[0];
    int64_t overall_maximum = array[0];

    for (size_t i = 1U; i < length; ++i) {
        int64_t product_with_maximum;
        int64_t product_with_minimum;

        if (!multiply_checked(array[i], maximum_ending,
                              &product_with_maximum) ||
            !multiply_checked(array[i], minimum_ending,
                              &product_with_minimum)) {
            return 0;
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

        maximum_ending = next_maximum;
        minimum_ending = next_minimum;

        if (maximum_ending > overall_maximum) {
            overall_maximum = maximum_ending;
        }
    }

    *maximum_product = overall_maximum;
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char extra;
    unsigned long long parsed;
    int consumed = 0;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (sscanf(buffer, " %llu %n%c", &parsed, &consumed, &extra) != 1) {
        return 0;
    }

    while (buffer[consumed] == ' ' || buffer[consumed] == '\t' ||
           buffer[consumed] == '\r' || buffer[consumed] == '\n') {
        ++consumed;
    }

    if (buffer[consumed] != '\0' || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t result;

    if (!read_size(&length) || length == 0U ||
        length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_product_subarray(array, length, &result)) {
        fputs("Unable to calculate maximum product\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}