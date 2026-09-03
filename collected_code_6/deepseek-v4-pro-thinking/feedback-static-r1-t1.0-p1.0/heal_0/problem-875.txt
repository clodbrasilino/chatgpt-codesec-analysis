#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

long long min_tuple_difference(const int tuples[][2], size_t count)
{
    long long min_diff = LLONG_MAX;
    size_t i;

    if (tuples == NULL || count == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        long long diff = llabs((long long)tuples[i][0] - (long long)tuples[i][1]);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void)
{
    int tuples[][2] = {
        {5, 10},
        {3, 8},
        {7, 7},
        {20, 15}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    long long min = min_tuple_difference(tuples, count);

    if (min < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%lld\n", min);
    return 0;
}