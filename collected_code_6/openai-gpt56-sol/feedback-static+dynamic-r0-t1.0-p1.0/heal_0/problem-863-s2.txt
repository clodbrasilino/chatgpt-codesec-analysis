#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static size_t longest_consecutive_subsequence(const int *values, size_t count)
{
    int *sorted = NULL;
    size_t current_length = 1;
    size_t longest_length = 1;

    if (values == NULL || count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*sorted)) {
        return 0;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    for (size_t i = 1; i < count; ++i) {
        if (sorted[i] == sorted[i - 1]) {
            continue;
        }

        if (sorted[i - 1] != INT_MAX && sorted[i] == sorted[i - 1] + 1) {
            ++current_length;
            if (current_length > longest_length) {
                longest_length = current_length;
            }
        } else {
            current_length = 1;
        }
    }

    free(sorted);
    return longest_length;
}

int main(void)
{
    int values[] = {100, 4, 200, 1, 3, 2, 2, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t result = longest_consecutive_subsequence(values, count);

    if (result == 0 && count != 0) {
        fputs("Unable to compute the result.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}