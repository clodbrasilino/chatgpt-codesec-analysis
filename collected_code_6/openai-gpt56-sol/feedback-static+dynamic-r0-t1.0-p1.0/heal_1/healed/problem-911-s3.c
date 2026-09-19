#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>

static int multiply_int64(int64_t a, int64_t b, int64_t *result)
{
    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return -1;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return -1;
        }
    }

    *result = a * b;
    return 0;
}

static int product_of_three(int a, int b, int c, int64_t *result)
{
    int64_t intermediate;

    if (multiply_int64((int64_t)a, (int64_t)b, &intermediate) != 0) {
        return -1;
    }

    return multiply_int64(intermediate, (int64_t)c, result);
}

static int maximum_product_of_three(const int array[], size_t length,
                                    int64_t *result)
{
    int largest1;
    int largest2;
    int largest3;
    int smallest1;
    int smallest2;
    int64_t product_largest;
    int64_t product_mixed;

    if (array == NULL || result == NULL || length < 3U) {
        return -1;
    }

    largest1 = array[0];
    largest2 = array[1];
    largest3 = array[2];

    if (largest1 < largest2) {
        int temp = largest1;
        largest1 = largest2;
        largest2 = temp;
    }

    if (largest2 < largest3) {
        int temp = largest2;
        largest2 = largest3;
        largest3 = temp;
    }

    if (largest1 < largest2) {
        int temp = largest1;
        largest1 = largest2;
        largest2 = temp;
    }

    smallest1 = array[0];
    smallest2 = array[1];

    if (smallest1 > smallest2) {
        int temp = smallest1;
        smallest1 = smallest2;
        smallest2 = temp;
    }

    for (size_t i = 3U; i < length; ++i) {
        int value = array[i];

        if (value >= largest1) {
            largest3 = largest2;
            largest2 = largest1;
            largest1 = value;
        } else if (value >= largest2) {
            largest3 = largest2;
            largest2 = value;
        } else if (value > largest3) {
            largest3 = value;
        }
    }

    for (size_t i = 2U; i < length; ++i) {
        int value = array[i];

        if (value <= smallest1) {
            smallest2 = smallest1;
            smallest1 = value;
        } else if (value < smallest2) {
            smallest2 = value;
        }
    }

    if (product_of_three(largest1, largest2, largest3,
                         &product_largest) != 0 ||
        product_of_three(smallest1, smallest2, largest1,
                         &product_mixed) != 0) {
        return -1;
    }

    *result = product_largest > product_mixed
                  ? product_largest
                  : product_mixed;

    return 0;
}

int main(void)
{
    size_t length;
    int *array;
    int64_t result;

    if (scanf("%zu", &length) != 1 ||
        length < 3U ||
        length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (maximum_product_of_three(array, length, &result) != 0) {
        fprintf(stderr, "Unable to compute maximum product\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);

    free(array);
    return EXIT_SUCCESS;
}