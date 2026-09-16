#include <stdio.h>
#include <stdlib.h>

static int count_inversions(const int *values, size_t length, size_t *count)
{
    if (values == NULL || count == NULL) {
        return 0;
    }

    *count = 0;

    for (size_t i = 0; i < length; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (values[i] > values[j]) {
                if (*count == SIZE_MAX) {
                    return 0;
                }
                ++(*count);
            }
        }
    }

    return 1;
}

static int inversion_counts_are_equal(const int *first, size_t first_length,
                                      const int *second, size_t second_length,
                                      int *are_equal)
{
    size_t first_count;
    size_t second_count;

    if (are_equal == NULL) {
        return 0;
    }

    if (!count_inversions(first, first_length, &first_count) ||
        !count_inversions(second, second_length, &second_count)) {
        return 0;
    }

    *are_equal = first_count == second_count;
    return 1;
}

int main(void)
{
    size_t first_length;
    size_t second_length;
    int *first = NULL;
    int *second = NULL;
    int are_equal;
    int result = EXIT_FAILURE;

    if (scanf("%zu %zu", &first_length, &second_length) != 2) {
        goto cleanup;
    }

    if (first_length > SIZE_MAX / sizeof(*first) ||
        second_length > SIZE_MAX / sizeof(*second)) {
        goto cleanup;
    }

    if (first_length > 0) {
        first = malloc(first_length * sizeof(*first));
        if (first == NULL) {
            goto cleanup;
        }
    }

    if (second_length > 0) {
        second = malloc(second_length * sizeof(*second));
        if (second == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < first_length; ++i) {
        if (scanf("%d", &first[i]) != 1) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < second_length; ++i) {
        if (scanf("%d", &second[i]) != 1) {
            goto cleanup;
        }
    }

    if (!inversion_counts_are_equal(first, first_length, second,
                                    second_length, &are_equal)) {
        goto cleanup;
    }

    puts(are_equal ? "Same" : "Not same");
    result = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return result;
}