#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int compare_tuples(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;

    if (tupleA->first < tupleB->first) {
        return -1;
    }
    if (tupleA->first > tupleB->first) {
        return 1;
    }
    if (tupleA->second < tupleB->second) {
        return -1;
    }
    if (tupleA->second > tupleB->second) {
        return 1;
    }
    return 0;
}

void sort_tuples(Tuple *array, size_t count) {
    if (array == NULL || count == 0) {
        return;
    }
    qsort(array, count, sizeof(Tuple), compare_tuples);
}

int main(void) {
    size_t count = 5;
    Tuple *tuples = (Tuple *)malloc(count * sizeof(Tuple));

    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuples[0].first = 5; tuples[0].second = 2;
    tuples[1].first = 1; tuples[1].second = 4;
    tuples[2].first = 3; tuples[2].second = 1;
    tuples[3].first = 3; tuples[3].second = 0;
    tuples[4].first = 1; tuples[4].second = 3;

    sort_tuples(tuples, count);

    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}