#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static bool multiply_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return false;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return false;
        }
    }

    *result = a * b;
    return true;
}

static bool find_minimum_product(const Tuple tuples[], size_t count, int64_t *minimum)
{
    if (tuples == NULL || minimum == NULL || count == 0) {
        return false;
    }

    bool found = false;
    int64_t min_product = 0;

    for (size_t i = 0; i < count; ++i) {
        int64_t product;

        if (!multiply_int64(tuples[i].first, tuples[i].second, &product)) {
            return false;
        }

        if (!found || product < min_product) {
            min_product = product;
            found = true;
        }
    }

    *minimum = min_product;
    return true;
}

int main(void)
{
    const Tuple tuples[] = {
        {3, 4},
        {-5, 6},
        {7, -8},
        {-2, -9},
        {0, 10}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int64_t minimum;

    if (!find_minimum_product(tuples, count, &minimum)) {
        fputs("Unable to determine the minimum product.\n", stderr);
        return 1;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        return 1;
    }

    return 0;
}