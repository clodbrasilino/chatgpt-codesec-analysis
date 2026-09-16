#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    
    if (tupleA->second < tupleB->second) {
        return -1;
    } else if (tupleA->second > tupleB->second) {
        return 1;
    } else {
        return 0;
    }
}

void sort_tuples(Tuple *tuples, size_t size) {
    if (tuples != NULL && size > 1) {
        qsort(tuples, size, sizeof(Tuple), compare_tuples);
    }
}

int main(void) {
    Tuple *tuples = malloc(5 * sizeof(Tuple));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].first = 1; tuples[0].second = 9;
    tuples[1].first = 2; tuples[1].second = 4;
    tuples[2].first = 3; tuples[2].second = 6;
    tuples[3].first = 4; tuples[3].second = 1;
    tuples[4].first = 5; tuples[4].second = 8;

    sort_tuples(tuples, 5);

    for (size_t i = 0; i < 5; ++i) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    free(tuples);
    return EXIT_SUCCESS;
}