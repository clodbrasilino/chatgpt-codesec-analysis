#include <stdio.h>

#define SIZE 2

void subtract_elements(int arr[SIZE][SIZE], int result[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = arr[i][0] - arr[i][1];
    }
}

int main() {
    int arr[SIZE][SIZE] = {{10, 5}, {20, 15}};
    int result[SIZE];

    subtract_elements(arr, result);

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}