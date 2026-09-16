#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int safe_accumulate(long long *acc, int value)
{
    if (acc == NULL) {
        return -1;
    }
    if (value > 0 && *acc > LLONG_MAX - value) {
        return -1;
    }
    if (value < 0 && *acc < LLONG_MIN - value) {
        return -1;
    }
    *acc += value;
    return 0;
}

int alternate_chain_sums(const Tuple *tuples, size_t count,
                         long long *sum_even, long long *sum_odd)
{
    size_t i;
    long long even_total = 0;
    long long odd_total = 0;

    if (tuples == NULL || sum_even == NULL || sum_odd == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (safe_accumulate(&even_total, tuples[i].first) != 0) {
            return -1;
        }
        if (safe_accumulate(&odd_total, tuples[i].second) != 0) {
            return -1;
        }
    }

    *sum_even = even_total;
    *sum_odd = odd_total;
    return 0;
}

int main(void)
{
    Tuple data[] = {
        {5, 6},
        {3, 6},
        {1, 8},
        {9, 12}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    long long sum_even = 0;
    long long sum_odd = 0;

    if (alternate_chain_sums(data, count, &sum_even, &sum_odd) != 0) {
        if (fprintf(stderr, "Error: failed to compute alternate chain sums\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Sum of first alternate chain: %lld\n", sum_even) < 0) {
        return EXIT_FAILURE;
    }
    if (printf("Sum of second alternate chain: %lld\n", sum_odd) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}