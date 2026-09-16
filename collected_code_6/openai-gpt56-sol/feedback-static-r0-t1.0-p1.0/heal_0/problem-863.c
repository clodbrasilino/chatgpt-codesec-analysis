#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static size_t longest_consecutive_subsequence(const int *values, size_t count)
{
    int *sorted;
    size_t current_length;
    size_t longest_length;

    if (values == NULL || count == 0U) {
        return 0U;
    }

    if (count > SIZE_MAX / sizeof(*sorted)) {
        return 0U;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return 0U;
    }

    for (size_t i = 0U; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    current_length = 1U;
    longest_length = 1U;

    for (size_t i = 1U; i < count; ++i) {
        if (sorted[i] == sorted[i - 1U]) {
            continue;
        }

        if ((long long)sorted[i] == (long long)sorted[i - 1U] + 1LL) {
            ++current_length;
            if (current_length > longest_length) {
                longest_length = current_length;
            }
        } else {
            current_length = 1U;
        }
    }

    free(sorted);
    return longest_length;
}

int main(void)
{
    int values[] = {100, 4, 200, 1, 3, 2, 2};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t result = longest_consecutive_subsequence(values, count);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}