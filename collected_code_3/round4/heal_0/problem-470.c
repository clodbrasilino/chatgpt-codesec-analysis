#include <stdio.h>

#define SIZE 3

void pairwiseAddition(int tuple1[], int tuple2[], int result[], int size) {
    for(int i = 0; i < size; i++) {
        result[i] = tuple1[i] + tuple2[i];
    }
}

int main() {
    int tuple1[SIZE] = {1, 2, 3};
    int tuple2[SIZE] = {4, 5, 6};
    int result[SIZE];

    pairwiseAddition(tuple1, tuple2, result, SIZE);

    printf("Pairwise addition of tuples is: ");
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}