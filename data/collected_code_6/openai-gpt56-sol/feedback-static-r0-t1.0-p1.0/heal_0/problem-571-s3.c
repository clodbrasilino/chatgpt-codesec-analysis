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

static long long maximum_pair_sum(int *values, size_t count, long long k)
{
    long long sum = 0;
    size_t i;

    if (values == NULL || count < 2U || k < 0) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);

    i = count;
    while (i >= 2U) {
        const long long larger = values[i - 1U];
        const long long smaller = values[i - 2U];

        if (larger - smaller < k) {
            sum += larger + smaller;
            i -= 2U;
        } else {
            --i;
        }
    }

    return sum;
}

int main(void)
{
    size_t count;
    long long k;
    int *values = NULL;
    long long result;
    size_t i;

    if (scanf("%zu %lld", &count, &k) != 2 || k < 0) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    result = maximum_pair_sum(values, count, k);
    printf("%lld\n", result);

    free(values);
    return EXIT_SUCCESS;
}