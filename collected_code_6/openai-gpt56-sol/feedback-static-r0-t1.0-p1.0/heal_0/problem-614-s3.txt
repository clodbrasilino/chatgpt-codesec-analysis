#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int cumulative_sum(const Tuple *tuples, size_t count, long long *result)
{
    size_t i;
    long long sum = 0;

    if (result == NULL || (tuples == NULL && count != 0)) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if ((tuples[i].first > 0 && sum > LLONG_MAX - tuples[i].first) ||
            (tuples[i].first < 0 && sum < LLONG_MIN - tuples[i].first)) {
            return -1;
        }
        sum += tuples[i].first;

        if ((tuples[i].second > 0 && sum > LLONG_MAX - tuples[i].second) ||
            (tuples[i].second < 0 && sum < LLONG_MIN - tuples[i].second)) {
            return -1;
        }
        sum += tuples[i].second;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long result;

    errno = 0;

    if (cumulative_sum(tuples, count, &result) != 0) {
        fputs("Failed to calculate cumulative sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}