#include <stdio.h>

#define SIZE 5

void subtractArrays(int a[], int b[], int subtract[], int size) {
    for(int i = 0; i < size; i++) {
        subtract[i] = a[i] - b[i];
    }
}

int main() {
    int a[SIZE] = {1, 2, 3, 4, 5};
    int b[SIZE] = {5, 4, 3, 2, 1};
    int subtract[SIZE];

    subtractArrays(a, b, subtract, SIZE);

    printf("Result of subtraction: ");
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", subtract[i]);
    }

    return 0;
}