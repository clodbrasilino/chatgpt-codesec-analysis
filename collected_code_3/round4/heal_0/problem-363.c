#include <stdio.h>

#define SIZE 5

void addK(int *arr, int n, int k) {
    for(int i = 0; i < n; i++) {
        arr[i] += k;
    }
}

int main() {
    int arr[SIZE] = {1, 2, 3, 4, 5};
    int k = 3;

    addK(arr, SIZE, k);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}