#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int last;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    if (tuple_a->last < tuple_b->last) return -1;
    if (tuple_a->last > tuple_b->last) return 1;
    return 0;
}

void sort_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL || count == 0) {
        return;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
}

int main(void) {
    size_t count = 5;
    Tuple *tuples = (Tuple *)malloc(count * sizeof(Tuple));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].first = 1; tuples[0].last = 9;
    tuples[1].first = 2; tuples[1].last = 5;
    tuples[2].first = 3; tuples[2].last = 7;
    tuples[3].first = 4; tuples[3].last = 1;
    tuples[4].first = 5; tuples[4].last = 3;

    sort_tuples(tuples, count);

    for (size_t i = 0; i < count; ++i) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].last);
    }

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}