#include <limits.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int first;
    int second;
} Pair;

static int maximum_pair_difference(const Pair pairs[], size_t count, long long *result)
{
    size_t i;
    long long maximum;

    if (pairs == NULL || result == NULL || count == 0U) {
        return 0;
    }

    maximum = (long long)pairs[0].first - (long long)pairs[0].second;

    if (maximum < 0) {
        maximum = -maximum;
    }

    for (i = 1U; i < count; ++i) {
        long long difference =
            (long long)pairs[i].first - (long long)pairs[i].second;

        if (difference < 0) {
            difference = -difference;
        }

        if (difference > maximum) {
            maximum = difference;
        }
    }

    *result = maximum;
    return 1;
}

int main(void)
{
    const Pair pairs[] = {
        {5, 1},
        {2, 9},
        {-3, 4},
        {INT_MIN, INT_MAX}
    };
    const size_t count = sizeof(pairs) / sizeof(pairs[0]);
    long long maximum;

    if (!maximum_pair_difference(pairs, count, &maximum)) {
        fputs("Unable to calculate the maximum difference.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", maximum) < 0) {
        return 1;
    }

    return 0;
}