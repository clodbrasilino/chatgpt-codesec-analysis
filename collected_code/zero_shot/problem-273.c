#include <stdio.h>

void subtractTuples(int tuple1[], int tuple2[], int result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = tuple1[i] - tuple2[i];
    }
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    int result[size];

    subtractTuples(tuple1, tuple2, result, size);

    printf("Subtraction Result: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}