#include <stdio.h>

#define SIZE 5

void convertListToTuple(int list[], int tuple[][2], int size) {
    for(int i = 0; i < size; i++) {
        tuple[i][0] = i;
        tuple[i][1] = list[i];
    }
}

int main() {
    int list[SIZE] = {1, 2, 3, 4, 5};
    int tuple[SIZE][2];

    convertListToTuple(list, tuple, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("(%d, %d)\n", tuple[i][0], tuple[i][1]);
    }

    return 0;
}