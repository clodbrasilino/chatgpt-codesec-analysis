#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((a > 0 && b > 0 && a > INT64_MAX / b) ||
        (a > 0 && b < 0 && b < INT64_MIN / a) ||
        (a < 0 && b > 0 && a < INT64_MIN / b) ||
        (a < 0 && b < 0 && a < INT64_MAX / b)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int find_minimum_product(const Tuple *tuples, size_t count, int64_t *minimum)
{
    int64_t product;

    if (tuples == NULL || minimum == NULL || count == 0U) {
        return 0;
    }

    if (!multiply_checked(tuples[0].first, tuples[0].second, minimum)) {
        return 0;
    }

    for (size_t i = 1U; i < count; ++i) {
        if (!multiply_checked(tuples[i].first, tuples[i].second, &product)) {
            return 0;
        }

        if (product < *minimum) {
            *minimum = product;
        }
    }

    return 1;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 4},
        {-5, 6},
        {-7, -2},
        {8, -3},
        {0, 10}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int64_t minimum;

    errno = 0;

    if (!find_minimum_product(tuples, count, &minimum)) {
        if (fputs("Unable to determine the minimum product.\n", stderr) == EOF) {
            return 2;
        }
        return 1;
    }

    if (printf("Minimum product: %" PRId64 "\n", minimum) < 0) {
        return 2;
    }

    return 0;
}