#include<stdio.h>

void extractElements(int tuple1[], int size1, int tuple2[], int size2) {
    int i;

    for(i = 0; i < size1; i++) {
        printf("Tuple 1 Element [%d]: %d \n", i, tuple1[i]);
    }

    for(i = 0; i < size2; i++) {
        printf("Tuple 2 Element [%d]: %d \n", i, tuple2[i]);
    }
}

void main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {6, 7, 8, 9, 10};

    int size1 = sizeof(tuple1)/sizeof(tuple1[0]);
    int size2 = sizeof(tuple2)/sizeof(tuple2[0]);

    extractElements(tuple1, size1, tuple2, size2);
}