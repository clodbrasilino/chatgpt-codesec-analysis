#include <stdio.h>
#include <stdlib.h>

void moduloTuples(int* tuple1, const int* tuple2, int size) {
    for (int i = 0; i < size; i++) {
        tuple1[i] = tuple1[i] % tuple2[i];
    }
}

int main() {
    int size = 5;
    int tuple1[] = {13, 5, 9, 4, 8};
    const int tuple2[] = {4, 2, 3, 2, 7};

    moduloTuples(tuple1, tuple2, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", tuple1[i]);
    }

    return 0;
}