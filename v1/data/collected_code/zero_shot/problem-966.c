#include <stdio.h>

void removeEmptyTuple(int tuples[][2], int *sizePtr) {
    int newSize = 0;
    for (int i = 0; i < *sizePtr; i++) {
        if (tuples[i][0] != 0 && tuples[i][1] != 0) {
            tuples[newSize][0] = tuples[i][0];
            tuples[newSize][1] = tuples[i][1];
            newSize++;
        }
    }
    *sizePtr = newSize;
}

int main() {
    int tuples[5][2] = { {1, 2}, {0, 0}, {3, 4}, {0, 0}, {5, 6} };
    int size = 5;

    removeEmptyTuple(tuples, &size);

    for (int i = 0; i < size; i++) {
        printf("(%d, %d) ", tuples[i][0], tuples[i][1]);
    }

    return 0;
}