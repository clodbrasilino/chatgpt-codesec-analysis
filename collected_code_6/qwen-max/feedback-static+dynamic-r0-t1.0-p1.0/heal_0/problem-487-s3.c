#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} tuple;

int compare_tuples(const void *a, const void *b) {
    tuple *tupleA = (tuple *)a;
    tuple *tupleB = (tuple *)b;
    return (*(tupleA->elements + tupleA->length - 1) - *(tupleB->elements + tupleB->length - 1));
}

void sort_tuples(tuple *tuples, size_t count) {
    qsort(tuples, count, sizeof(tuple), compare_tuples);
}

int main() {
    tuple tuples[] = {
        {{1, 3, 5}, 3},
        {{2, 4, 1}, 3},
        {{7, 8, 9}, 3}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, count);

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < tuples[i].length; j++) {
            printf("%d ", tuples[i].elements[j]);
        }
        printf("\n");
    }

    return 0;
}