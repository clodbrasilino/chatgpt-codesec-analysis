#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int arithmetic_term(int64_t first, int64_t difference, int64_t term,
                           int64_t *result)
{
    int64_t steps;

    if (result == NULL || term < 1) {
        return 0;
    }

    steps = term - 1;

#if defined(__GNUC__) || defined(__clang__)
    int64_t product;

    if (__builtin_mul_overflow(steps, difference, &product) ||
        __builtin_add_overflow(first, product, result)) {
        return 0;
    }
#else
    if (difference > 0) {
        if (steps > (uint64_t)(INT64_MAX - first) / (uint64_t)difference) {
            return 0;
        }
    } else if (difference < 0) {
        uint64_t magnitude = UINT64_C(0) - (uint64_t)difference;
        uint64_t capacity = (uint64_t)first - (uint64_t)INT64_MIN;

        if ((uint64_t)steps > capacity / magnitude) {
            return 0;
        }
    }

    *result = first + steps * difference;
#endif

    return 1;
}

int main(void)
{
    int64_t first;
    int64_t difference;
    int64_t term;
    int64_t result;

    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64,
              &first, &difference, &term) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!arithmetic_term(first, difference, term, &result)) {
        fputs("Invalid term or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}