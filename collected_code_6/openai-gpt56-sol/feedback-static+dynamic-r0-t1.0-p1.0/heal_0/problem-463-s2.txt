#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int maximum_product_subarray(const int64_t *array, size_t length,
                                    int64_t *maximum_product)
{
    int64_t current_max;
    int64_t current_min;
    int64_t result;

    if (array == NULL || maximum_product == NULL || length == 0) {
        return 0;
    }

    current_max = array[0];
    current_min = array[0];
    result = array[0];

    for (size_t i = 1; i < length; ++i) {
        int64_t product_with_max;
        int64_t product_with_min;
        int64_t next_max;
        int64_t next_min;

        if (!multiply_checked(current_max, array[i], &product_with_max) ||
            !multiply_checked(current_min, array[i], &product_with_min)) {
            return 0;
        }

        next_max = array[i];
        if (product_with_max > next_max) {
            next_max = product_with_max;
        }
        if (product_with_min > next_max) {
            next_max = product_with_min;
        }

        next_min = array[i];
        if (product_with_max < next_min) {
            next_min = product_with_max;
        }
        if (product_with_min < next_min) {
            next_min = product_with_min;
        }

        current_max = next_max;
        current_min = next_min;

        if (current_max > result) {
            result = current_max;
        }
    }

    *maximum_product = result;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            goto cleanup;
        }
    }

    if (!maximum_product_subarray(array, length, &result)) {
        fprintf(stderr, "Product overflow or invalid input.\n");
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Output failed.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    return status;
}