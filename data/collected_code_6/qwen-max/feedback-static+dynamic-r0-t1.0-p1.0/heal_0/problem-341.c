#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

int compare(const void *a, const void *b) {
    Tuple *tupleA = (Tuple *)a;
    Tuple *tupleB = (Tuple *)b;
    if (tupleA->x == tupleB->x) {
        return tupleA->y - tupleB->y;
    }
    return tupleA->x - tupleB->x;
}

void convertToOrderedTuples(Tuple *tuples, int n) {
    qsort(tuples, n, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{3, 4}, {1, 2}, {3, 1}, {2, 5}, {1, 3}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    convertToOrderedTuples(tuples, n);

    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", tuples[i].x, tuples[i].y);
    }

    return 0;
}