#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

void rearrangeTuples(Tuple* tuples, int* order, int size) {
    Tuple* temp = (Tuple*)malloc(size * sizeof(Tuple));

    for(int i = 0; i < size; i++) {
        temp[i] = tuples[order[i]];
    }

    for(int i = 0; i < size; i++) {
        tuples[i] = temp[i];
    }

    free(temp);
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int order[] = {2, 0, 3, 1};
    int size = sizeof(tuples) / sizeof(Tuple);

    rearrangeTuples(tuples, order, size);

    for(int i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].x, tuples[i].y);
    }

    return 0;
}