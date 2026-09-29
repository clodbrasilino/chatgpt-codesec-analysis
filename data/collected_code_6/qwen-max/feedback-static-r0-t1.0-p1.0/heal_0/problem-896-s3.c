#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} Tuple;

int compare(const void *a, const void *b) {
    Tuple *tupleA = (Tuple *)a;
    Tuple *tupleB = (Tuple *)b;
    return tupleA->data[tupleA->len - 1] - tupleB->data[tupleB->len - 1];
}

void sortTuplesByLastElement(Tuple *tuples, size_t n) {
    qsort(tuples, n, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {
        { .data = (int[]){1, 3, 5}, .len = 3 },
        { .data = (int[]){2, 4, 1}, .len = 3 },
        { .data = (int[]){5, 6, 3}, .len = 3 }
    };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    
    sortTuplesByLastElement(tuples, n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < tuples[i].len; ++j) {
            printf("%d ", tuples[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}