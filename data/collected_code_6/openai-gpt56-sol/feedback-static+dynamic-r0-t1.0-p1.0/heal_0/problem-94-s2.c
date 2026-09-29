#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    double value;
} Tuple;

int find_min_value_index(const Tuple *tuples, size_t count, int *result)
{
    if (tuples == NULL || result == NULL || count == 0) {
        return -1;
    }

    size_t min_position = 0;

    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].value < tuples[min_position].value) {
            min_position = i;
        }
    }

    *result = tuples[min_position].index;
    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {10, 4.5},
        {20, 2.1},
        {30, 7.8},
        {40, -1.3},
        {50, 0.0}
    };
    const size_t count = sizeof tuples / sizeof tuples[0];
    int minimum_index;

    if (find_min_value_index(tuples, count, &minimum_index) != 0) {
        fputs("Failed to find the minimum-value record.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", minimum_index) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}