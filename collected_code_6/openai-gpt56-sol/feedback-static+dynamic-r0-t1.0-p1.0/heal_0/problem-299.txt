#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static bool calculate_maximum_aggregate(const Tuple *tuples,
                                        size_t count,
                                        int64_t *maximum)
{
    if (tuples == NULL || maximum == NULL || count == 0U) {
        return false;
    }

    if ((tuples[0].second > 0 &&
         tuples[0].first > INT64_MAX - tuples[0].second) ||
        (tuples[0].second < 0 &&
         tuples[0].first < INT64_MIN - tuples[0].second)) {
        return false;
    }

    *maximum = tuples[0].first + tuples[0].second;

    for (size_t i = 1U; i < count; ++i) {
        int64_t aggregate;

        if ((tuples[i].second > 0 &&
             tuples[i].first > INT64_MAX - tuples[i].second) ||
            (tuples[i].second < 0 &&
             tuples[i].first < INT64_MIN - tuples[i].second)) {
            return false;
        }

        aggregate = tuples[i].first + tuples[i].second;

        if (aggregate > *maximum) {
            *maximum = aggregate;
        }
    }

    return true;
}

int main(void)
{
    const Tuple tuples[] = {
        {4, 7},
        {10, -2},
        {3, 15},
        {-8, 5}
    };
    int64_t maximum;

    if (!calculate_maximum_aggregate(
            tuples, sizeof(tuples) / sizeof(tuples[0]), &maximum)) {
        fputs("Unable to calculate maximum aggregate.\n", stderr);
        return 1;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        return 1;
    }

    return 0;
}