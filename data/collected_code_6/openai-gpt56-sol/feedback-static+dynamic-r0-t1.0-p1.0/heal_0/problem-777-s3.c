#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int sum_non_repeated(const int64_t *array, size_t length, int64_t *sum)
{
    if (array == NULL || sum == NULL || length == 0U) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    int64_t *copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_int64);

    int64_t result = 0;
    size_t i = 0U;

    while (i < length) {
        size_t j = i + 1U;

        while (j < length && copy[j] == copy[i]) {
            ++j;
        }

        if (j - i == 1U) {
            if ((copy[i] > 0 && result > INT64_MAX - copy[i]) ||
                (copy[i] < 0 && result < INT64_MIN - copy[i])) {
                free(copy);
                return -1;
            }
            result += copy[i];
        }

        i = j;
    }

    free(copy);
    *sum = result;
    return 0;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1 || length == 0U ||
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

    int64_t sum = 0;
    if (sum_non_repeated(array, length, &sum) != 0) {
        fputs("Unable to calculate sum\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}