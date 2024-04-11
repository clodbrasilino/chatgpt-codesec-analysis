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

void sortTuples(Tuple* tuples, int count) {
    qsort(tuples, count, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{1, 3}, {2, 1}, {3, 2}};
    int count = sizeof(tuples) / sizeof(Tuple);

    sortTuples(tuples, count);

    for(int i = 0; i < count; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].last);
    }

    return 0;
}