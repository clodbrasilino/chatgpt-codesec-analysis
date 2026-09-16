#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static size_t minimum_removals(int *values, size_t count, long long k)
{
    if (values == NULL || count == 0U) {
        return 0U;
    }

    if (k < 0) {
        return count;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    size_t left = 0U;
    size_t maximum_kept = 0U;

    for (size_t right = 0U; right < count; ++right) {
        while ((long long)values[right] - (long long)values[left] > k) {
            ++left;
        }

        const size_t kept = right - left + 1U;
        if (kept > maximum_kept) {
            maximum_kept = kept;
        }
    }

    return count - maximum_kept;
}

int main(void)
{
    size_t count = 0U;
    long long k = 0;

    if (scanf("%zu %lld", &count, &k) != 2) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count > 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < count; ++i) {
            if (scanf("%d", &values[i]) != 1) {
                free(values);
                return EXIT_FAILURE;
            }
        }
    }

    const size_t result = minimum_removals(values, count, k);

    if (printf("%zu\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}