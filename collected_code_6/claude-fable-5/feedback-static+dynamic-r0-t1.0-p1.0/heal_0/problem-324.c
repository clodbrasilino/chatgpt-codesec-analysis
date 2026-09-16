#include <stdio.h>
#include <stddef.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int safe_add(long long *acc, int value)
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
                         long long *even_sum, long long *odd_sum)
{
    size_t i;
    long long e = 0;
    long long o = 0;

    if (tuples == NULL || even_sum == NULL || odd_sum == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (safe_add(&e, tuples[i].first) != 0) {
            return -1;
        }
        if (safe_add(&o, tuples[i].second) != 0) {
            return -1;
        }
    }

    *even_sum = e;
    *odd_sum = o;
    return 0;
}

int main(void)
{
    Tuple data[] = {
        {5, 6},
        {3, 6},
        {7, 2},
        {1, 4}
    };
    size_t count = sizeof(data) / sizeof(data[0]);
    long long even_sum = 0;
    long long odd_sum = 0;

    if (alternate_chain_sums(data, count, &even_sum, &odd_sum) != 0) {
        fprintf(stderr, "Error computing alternate chain sums\n");
        return 1;
    }

    if (printf("Even chain sum: %lld\n", even_sum) < 0) {
        return 1;
    }
    if (printf("Odd chain sum: %lld\n", odd_sum) < 0) {
        return 1;
    }

    return 0;
}