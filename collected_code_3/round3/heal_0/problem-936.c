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
    int size = 5;
    Tuple tuples[5] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int order[5] = {4, 3, 2, 1, 0};

    rearrangeTuples(tuples, order, size);

    for(int i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].x, tuples[i].y);
    }

    return 0;
}