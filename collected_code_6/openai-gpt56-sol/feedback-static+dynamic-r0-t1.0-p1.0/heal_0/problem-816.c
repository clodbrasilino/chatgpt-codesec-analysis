#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int clear_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL && count != 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        tuples[i].first = 0;
        tuples[i].second = 0;
    }

    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const size_t count = sizeof tuples / sizeof tuples[0];

    if (clear_tuples(tuples, count) != 0) {
        fputs("Failed to clear tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            fputs("Failed to write output.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}