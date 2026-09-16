#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool find_common_first(const Tuple *tuples, size_t count, int *result)
{
    if (tuples == NULL || result == NULL || count == 0U) {
        return false;
    }

    int candidate = tuples[0].first;

    for (size_t i = 1U; i < count; ++i) {
        if (tuples[i].first != candidate) {
            return false;
        }
    }

    *result = candidate;
    return true;
}

int main(void)
{
    Tuple tuples[] = {
        {10, 1},
        {10, 2},
        {10, 3},
        {10, 4}
    };
    size_t count = sizeof tuples / sizeof tuples[0];
    int common_first = 0;

    if (!find_common_first(tuples, count, &common_first)) {
        if (fprintf(stderr, "No common first element found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Common first element: %d\n", common_first) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}