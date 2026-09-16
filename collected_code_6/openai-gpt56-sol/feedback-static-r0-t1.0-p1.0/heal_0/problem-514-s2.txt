#include <stdio.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

int sum_tuple_elements(const Tuple *tuples, size_t count, long long *result)
{
    size_t i;
    long long sum = 0;

    if (result == NULL || (tuples == NULL && count != 0U)) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        sum += (long long)tuples[i].first;
        sum += (long long)tuples[i].second;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long sum;

    if (sum_tuple_elements(tuples, count, &sum) != 0) {
        fputs("Failed to calculate the sum.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", sum) < 0) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}