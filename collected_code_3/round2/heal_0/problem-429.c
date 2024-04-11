#include <stdio.h>

#define SIZE 5

void extractElements(int tuple1[], int tuple2[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("(%d, %d)\n", tuple1[i], tuple2[i]);
    }
}

int main() {
    int tuple1[SIZE] = {1, 2, 3, 4, 5};
    int tuple2[SIZE] = {6, 7, 8, 9, 10};

    extractElements(tuple1, tuple2, SIZE);

    return 0;
}