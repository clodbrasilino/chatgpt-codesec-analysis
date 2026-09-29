#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef int (*CompareFunc)(const Tuple*, const Tuple*);

int compare_first_asc(const Tuple *a, const Tuple *b) {
    return a->first - b->first;
}

int compare_first_desc(const Tuple *a, const Tuple *b) {
    return b->first - a->first;
}

int compare_second_asc(const Tuple *a, const Tuple *b) {
    return a->second - b->second;
}

int compare_second_desc(const Tuple *a, const Tuple *b) {
    return b->second - a->second;
}

void sort_tuples(Tuple *tuples, size_t count, CompareFunc cmp) {
    if (tuples == NULL || cmp == NULL || count <= 1) {
        return;
    }
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - 1 - i; j++) {
            if (cmp(&tuples[j], &tuples[j + 1]) > 0) {
                Tuple temp = tuples[j];
                tuples[j] = tuples[j + 1];
                tuples[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    Tuple tuples[] = {
        {3, 10},
        {1, 20},
        {2, 5},
        {5, 1},
        {4, 15}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, count, compare_first_asc);
    printf("Sorted by first ascending:\n");
    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    sort_tuples(tuples, count, compare_second_desc);
    printf("Sorted by second descending:\n");
    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d) ", tuples[i].first, tuples[i].second);
    }
    printf("\n");

    return 0;
}