#include <stdio.h>

void maximizeTuples(int tuple1[], int tuple2[], int size) {
    for (int i = 0; i < size; i++) {
        if (tuple1[i] < tuple2[i]) {
            tuple1[i] = tuple2[i];
        }
    }
}

int main() {
    int tuple1[] = {1, 5, 9};
    int tuple2[] = {2, 3, 8};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);

    maximizeTuples(tuple1, tuple2, size);

    printf("Maximized tuple1: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tuple1[i]);
    }

    return 0;
}