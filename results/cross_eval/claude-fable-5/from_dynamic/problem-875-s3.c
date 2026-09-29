#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int first;
    int second;
};

static int abs_diff(int a, int b)
{
    long diff = (long)a - (long)b;
    if (diff < 0) {
        diff = -diff;
    }
    return (int)diff;
}

static int min_difference(const struct Pair *pairs, size_t count, int *result)
{
    size_t i;
    int min;
    int current;

    if (pairs == NULL || result == NULL || count == 0U) {
        return -1;
    }

    min = abs_diff(pairs[0].first, pairs[0].second);
    for (i = 1U; i < count; i++) {
        current = abs_diff(pairs[i].first, pairs[i].second);
        if (current < min) {
            min = current;
        }
    }

    *result = min;
    return 0;
}

int main(void)
{
    struct Pair pairs[] = {
        {3, 5},
        {1, 7},
        {10, 3},
        {1, 2}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    int result = 0;

    if (min_difference(pairs, count, &result) != 0) {
        if (fprintf(stderr, "Error: invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Minimum difference: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}