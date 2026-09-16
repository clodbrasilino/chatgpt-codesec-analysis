#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

void clear_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        tuples[i] = (Tuple){0, 0};
    }
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    const size_t count = sizeof tuples / sizeof tuples[0];

    clear_tuples(tuples, count);

    for (size_t i = 0; i < count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}