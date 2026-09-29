#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_min_difference(const Tuple *tuples, size_t count, int *result)
{
    if (tuples == NULL || result == NULL || count == 0) {
        return -1;
    }

    long long min_diff = LLONG_MAX;

    for (size_t i = 0; i < count; i++) {
        long long diff = (long long)tuples[i].first - (long long)tuples[i].second;
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    if (min_diff > INT_MAX) {
        return -2;
    }

    *result = (int)min_diff;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {3, 5},
        {1, 7},
        {10, 3},
        {1, 2}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int result = 0;

    if (find_min_difference(tuples, count, &result) != 0) {
        fprintf(stderr, "Error: unable to compute minimum difference\n");
        return EXIT_FAILURE;
    }

    printf("Minimum difference: %d\n", result);
    return EXIT_SUCCESS;
}