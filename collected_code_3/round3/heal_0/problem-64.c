#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void* a, const void* b) {
    Tuple* tupleA = (Tuple*) a;
    Tuple* tupleB = (Tuple*) b;
    return tupleA->first - tupleB->first;
}

void sortTuples(Tuple* tuples, size_t size) {
    qsort(tuples, size, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{3, 4}, {1, 2}, {5, 6}, {2, 3}};
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, size);

    for(size_t i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}