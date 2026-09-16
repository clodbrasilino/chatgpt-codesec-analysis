#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_odd_length_subarrays(const int *array, size_t length, int64_t *result)
{
    if (array == NULL || result == NULL) {
        return -1;
    }

    int64_t sum = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t subarrays = (i + 1) * (length - i);
        size_t odd_subarrays = (subarrays + 1) / 2;

        if (__builtin_mul_overflow((int64_t)array[i], (int64_t)odd_subarrays,
                                   &(int64_t){0})) {
            return -1;
        }

        int64_t contribution = (int64_t)array[i] * (int64_t)odd_subarrays;

        if (__builtin_add_overflow(sum, contribution, &sum)) {
            return -1;
        }
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
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

    int64_t result;
    if (sum_odd_length_subarrays(array, length, &result) != 0) {
        fprintf(stderr, "Arithmetic overflow\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);

    return EXIT_SUCCESS;
}