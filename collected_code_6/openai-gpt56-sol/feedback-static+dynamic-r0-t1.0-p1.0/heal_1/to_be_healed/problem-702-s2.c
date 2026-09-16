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
    size_t max_kept = 0;

    if (values == NULL || count == 0) {
        return 0;
    }

    if (k < 0) {
        return count;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    for (size_t right = 0; right < count; ++right) {
        /* Possible weaknesses found:
         *  Assuming that condition 'left<=right' is not redundant
         */
        while (left <= right &&
               (long long)values[right] - (long long)values[left] > k) {
            ++left;
        }

        /* Possible weaknesses found:
         *  Assignment 'kept=right-left+1', assigned value is less than 1
         */
        const size_t kept = right - left + 1;
        /* Possible weaknesses found:
         *  Condition 'kept>max_kept' is always false [knownConditionTrueFalse]
         *  Condition 'kept>max_kept' is always false
         */
        if (kept > max_kept) {
            max_kept = kept;
        }
    }

    return count - max_kept;
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

    if (printf("%zu\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}