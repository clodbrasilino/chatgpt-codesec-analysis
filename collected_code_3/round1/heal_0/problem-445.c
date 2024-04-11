#include <stdio.h>

#define SIZE 5

void multiply_tuples(int tuple1[], int tuple2[], int result[], int size) {
    for(int i = 0; i < size; i++) {
        result[i] = tuple1[i] * tuple2[i];
    }
}

int main() {
    int tuple1[SIZE] = {1, 2, 3, 4, 5};
    int tuple2[SIZE] = {6, 7, 8, 9, 10};
    int result[SIZE];

    multiply_tuples(tuple1, tuple2, result, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}