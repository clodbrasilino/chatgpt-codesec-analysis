#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_maximum_difference(const Tuple *tuples, size_t count, long long *result)
{
    long long maximum;

    if (tuples == NULL || result == NULL || count == 0) {
        return -1;
    }

    maximum = llabs((long long)tuples[0].first - (long long)tuples[0].second);

    for (size_t i = 1; i < count; ++i) {
        long long difference =
            llabs((long long)tuples[i].first - (long long)tuples[i].second);

        if (difference > maximum) {
            maximum = difference;
        }
    }

    *result = maximum;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 8},
        {10, 2},
        {-4, 7},
        {INT_MIN, INT_MAX}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long maximum_difference;

    if (find_maximum_difference(tuples, count, &maximum_difference) != 0) {
        fputs("Unable to calculate the maximum difference.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", maximum_difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}