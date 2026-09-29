#include <stdio.h>

#define SIZE 5

void subtract_arrays(int a[], int b[], int c[], int size) {
    for(int i = 0; i < size; i++) {
        c[i] = a[i] - b[i];
    }
}

int main() {
    int a[SIZE] = {10, 20, 30, 40, 50};
    int b[SIZE] = {1, 2, 3, 4, 5};
    int c[SIZE];

    subtract_arrays(a, b, c, SIZE);

    printf("Result: ");
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}