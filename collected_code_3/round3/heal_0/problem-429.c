#include <stdio.h>

#define SIZE 5

void extract_elements(int tuple1[], int tuple2[], int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("Element %d from tuple1: %d\n", i+1, tuple1[i]);
        printf("Element %d from tuple2: %d\n", i+1, tuple2[i]);
    }
}

void extract_tuples(int tuple1[], int tuple2[], int size) {
    int i;
    printf("Tuple1: ");
    for(i = 0; i < size; i++) {
        printf("%d ", tuple1[i]);
    }
    printf("\nTuple2: ");
    for(i = 0; i < size; i++) {
        printf("%d ", tuple2[i]);
    }
    printf("\n");
}

int main() {
    int tuple1[SIZE] = {1, 2, 3, 4, 5};
    int tuple2[SIZE] = {6, 7, 8, 9, 10};

    extract_elements(tuple1, tuple2, SIZE);
    extract_tuples(tuple1, tuple2, SIZE);

    return 0;
}