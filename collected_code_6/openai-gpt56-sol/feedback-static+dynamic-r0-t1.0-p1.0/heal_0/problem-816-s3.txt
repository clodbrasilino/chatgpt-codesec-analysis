#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

static void clear_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0U; i < count; ++i) {
        tuples[i].first = 0;
        tuples[i].second = 0;
    }
}

int main(void)
{
    const size_t count = 3U;
    Tuple *tuples = calloc(count, sizeof(*tuples));

    if (tuples == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    tuples[0] = (Tuple){1, 2};
    tuples[1] = (Tuple){3, 4};
    tuples[2] = (Tuple){5, 6};

    clear_tuples(tuples, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%d, %d)\n", tuples[i].first, tuples[i].second) < 0) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    free(tuples);
    return EXIT_SUCCESS;
}