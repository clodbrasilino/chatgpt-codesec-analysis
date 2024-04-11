#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int last;
} Tuple;

int compare(const void* a, const void* b) {
    Tuple* tupleA = (Tuple*) a;
    Tuple* tupleB = (Tuple*) b;
    return tupleA->last - tupleB->last;
}

void sortTuples(Tuple* tuples, int size) {
    qsort(tuples, size, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{1, 5}, {2, 3}, {3, 1}, {4, 4}, {5, 2}};
    int size = sizeof(tuples) / sizeof(Tuple);

    sortTuples(tuples, size);

    for(int i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].last);
    }

    return 0;
}