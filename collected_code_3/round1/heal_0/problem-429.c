#include <stdio.h>

#define SIZE 3

void extractElements(int tuple1[], int tuple2[], int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuple1[i], tuple2[i]);
    }
}

int main() {
    int tuple1[SIZE] = {1, 2, 3};
    int tuple2[SIZE] = {4, 5, 6};

    extractElements(tuple1, tuple2, SIZE);

    return 0;
}