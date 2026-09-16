#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static size_t minimum_removals(int *values, size_t count, long long k)
{
    size_t left = 0;
    size_t longest = 0;

    if (values == NULL || count == 0) {
        return 0;
    }

    if (k < 0) {
        return count;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    for (size_t right = 0; right < count; ++right) {
        while ((long long)values[right] - (long long)values[left] > k) {
            ++left;
        }

        const size_t length = right - left + 1;
        if (length > longest) {
            longest = length;
        }
    }

    return count - longest;
}

int main(void)
{
    size_t count;
    long long k;

    if (scanf("%zu %lld", &count, &k) != 2) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count > 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    const size_t result = minimum_removals(values, count, k);
    printf("%zu\n", result);

    free(values);
    return EXIT_SUCCESS;
}