#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int cumulative_sum(const Tuple *tuples, size_t count, int64_t *sum)
{
    int64_t total = 0;

    if (sum == NULL || (tuples == NULL && count != 0U)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!add_checked(total, tuples[i].first, &total) ||
            !add_checked(total, tuples[i].second, &total)) {
            return 0;
        }
    }

    *sum = total;
    return 1;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const size_t count = sizeof tuples / sizeof tuples[0];
    int64_t sum;

    errno = 0;

    if (!cumulative_sum(tuples, count, &sum)) {
        fputs("Unable to calculate the cumulative sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}