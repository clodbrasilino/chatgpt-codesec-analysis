#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static size_t longest_consecutive_subsequence(const int *values, size_t count)
{
    int *sorted;
    size_t longest = 1;
    size_t current = 1;

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

        if ((int64_t)sorted[i] - (int64_t)sorted[i - 1] == 1) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 1;
        }
    }

    free(sorted);
    return longest;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count == 0) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    size_t result = longest_consecutive_subsequence(values, count);
    free(values);

    if (result == 0) {
        return EXIT_FAILURE;
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}