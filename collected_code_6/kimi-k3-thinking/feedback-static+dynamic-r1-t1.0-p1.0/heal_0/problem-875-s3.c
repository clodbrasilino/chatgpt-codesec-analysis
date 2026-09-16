#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Tuple {
    int first;
    int second;
};

int find_min_difference(const struct Tuple *tuples, size_t count, int *min_diff)
{
    size_t i;
    long long best;
    long long diff;

    if (tuples == NULL || min_diff == NULL || count == 0U) {
        return -1;
    }

    best = LLONG_MAX;

    for (i = 0U; i < count; i++) {
        diff = (long long)tuples[i].first - (long long)tuples[i].second;
        if (diff < 0LL) {
            diff = -diff;
        }
        if (diff < best) {
            best = diff;
        }
    }

    if (best > (long long)INT_MAX) {
        return -1;
    }

    *min_diff = (int)best;
    return 0;
}

int main(void)
{
    struct Tuple tuples[] = {
        { 3, 8 },
        { 10, 4 },
        { 7, 9 },
        { 15, 12 },
        { 20, 25 }
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    int min_diff = 0;

    if (find_min_difference(tuples, count, &min_diff) != 0) {
        fprintf(stderr, "Failed to compute minimum difference.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum difference: %d\n", min_diff);

    return EXIT_SUCCESS;
}