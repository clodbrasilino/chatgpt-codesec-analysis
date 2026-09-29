#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int clear_tuples(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        tuples[i].first = 0;
        tuples[i].second = 0;
    }

    return 0;
}

int main(void)
{
    Tuple tuples[3] = { {1, 2}, {3, 4}, {5, 6} };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    printf("Before clearing:\n");
    for (i = 0; i < count; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    if (clear_tuples(tuples, count) != 0) {
        fprintf(stderr, "Error: failed to clear tuples\n");
        return EXIT_FAILURE;
    }

    printf("After clearing:\n");
    for (i = 0; i < count; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    return EXIT_SUCCESS;
}