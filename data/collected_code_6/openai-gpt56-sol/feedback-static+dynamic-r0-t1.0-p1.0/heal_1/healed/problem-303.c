#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

static bool count_inversions(const int *array, size_t length,
                             unsigned long long *count)
{
    if ((array == NULL && length != 0U) || count == NULL) {
        return false;
    }

    *count = 0ULL;

    for (size_t i = 0U; i < length; ++i) {
        for (size_t j = i + 1U; j < length; ++j) {
            if (array[i] > array[j]) {
                if (*count == ULLONG_MAX) {
                    return false;
                }
                ++(*count);
            }
        }
    }

    return true;
}

static bool inversion_counts_are_equal(const int *first,
                                       size_t first_length,
                                       const int *second,
                                       size_t second_length,
                                       bool *result)
{
    unsigned long long first_count;
    unsigned long long second_count;

    if (result == NULL ||
        (first == NULL && first_length != 0U) ||
        (second == NULL && second_length != 0U)) {
        return false;
    }

    if (!count_inversions(first, first_length, &first_count) ||
        !count_inversions(second, second_length, &second_count)) {
        return false;
    }

    *result = first_count == second_count;
    return true;
}

static bool read_array(int **array, size_t length)
{
    int *values = NULL;

    if (array == NULL || length > SIZE_MAX / sizeof(*values)) {
        return false;
    }

    if (length != 0U) {
        values = malloc(length * sizeof(*values));
        if (values == NULL) {
            return false;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (scanf("%d", &values[i]) != 1) {
                free(values);
                return false;
            }
        }
    }

    *array = values;
    return true;
}

int main(void)
{
    size_t first_length;
    size_t second_length;
    int *first = NULL;
    int *second = NULL;
    bool result;

    if (scanf("%zu %zu", &first_length, &second_length) != 2) {
        return EXIT_FAILURE;
    }

    if (!read_array(&first, first_length)) {
        return EXIT_FAILURE;
    }

    if (!read_array(&second, second_length)) {
        free(first);
        return EXIT_FAILURE;
    }

    if (!inversion_counts_are_equal(first, first_length,
                                    second, second_length, &result)) {
        free(second);
        free(first);
        return EXIT_FAILURE;
    }

    puts(result ? "Same" : "Different");

    free(second);
    free(first);
    return EXIT_SUCCESS;
}