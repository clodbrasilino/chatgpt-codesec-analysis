#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long first;
    long long second;
} Pair;

static int compare_long_long(const void *left, const void *right)
{
    const long long a = *(const long long *)left;
    const long long b = *(const long long *)right;

    return (a > b) - (a < b);
}

static int find_maximum_difference(const Pair *pairs, size_t count,
                                   long long *maximum_difference)
{
    long long *first_values = NULL;
    long long *second_values = NULL;
    size_t first_index = 0;
    size_t second_index = 0;
    long long maximum = -1;

    if (pairs == NULL || maximum_difference == NULL || count == 0 ||
        count > SIZE_MAX / sizeof(*first_values)) {
        return 0;
    }

    first_values = malloc(count * sizeof(*first_values));
    second_values = malloc(count * sizeof(*second_values));

    if (first_values == NULL || second_values == NULL) {
        free(first_values);
        free(second_values);
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        first_values[i] = pairs[i].first;
        second_values[i] = pairs[i].second;
    }

    qsort(first_values, count, sizeof(*first_values), compare_long_long);
    qsort(second_values, count, sizeof(*second_values), compare_long_long);

    while (first_index < count && second_index < count) {
        if (first_values[first_index] < second_values[second_index]) {
            const long long difference =
                second_values[second_index] - first_values[first_index];

            if (difference > maximum) {
                maximum = difference;
            }
            ++first_index;
            ++second_index;
        } else {
            ++second_index;
        }
    }

    free(first_values);
    free(second_values);

    if (maximum < 0) {
        return 0;
    }

    *maximum_difference = maximum;
    return 1;
}

int main(void)
{
    const Pair pairs[] = {
        {2, 3},
        {1, 4},
        {5, 8},
        {7, 9}
    };
    const size_t count = sizeof(pairs) / sizeof(pairs[0]);
    long long maximum_difference = 0;

    if (!find_maximum_difference(pairs, count, &maximum_difference)) {
        fputs("Unable to find a valid pairing.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%lld\n", maximum_difference);
    return EXIT_SUCCESS;
}