#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int count_equal_pairs(const int *array, size_t length, uint64_t *pair_count)
{
    int *copy;
    uint64_t total = 0;

    if (pair_count == NULL || (array == NULL && length != 0)) {
        return -1;
    }

    *pair_count = 0;

    if (length < 2) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (size_t i = 0; i < length;) {
        size_t j = i + 1;

        while (j < length && copy[j] == copy[i]) {
            ++j;
        }

        const uint64_t occurrences = (uint64_t)(j - i);

        if (occurrences > 1) {
            const uint64_t first = occurrences;
            const uint64_t second = occurrences - 1;

            if ((first & 1U) == 0U) {
                total += (first / 2U) * second;
            } else {
                total += first * (second / 2U);
            }
        }

        i = j;
    }

    free(copy);
    *pair_count = total;
    return 0;
}

int main(void)
{
    size_t length;
    int *array = NULL;
    uint64_t pair_count;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (count_equal_pairs(array, length, &pair_count) != 0) {
        fputs("Unable to count equal pairs.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", pair_count);

    free(array);
    return EXIT_SUCCESS;
}