#include<stdio.h>

void shift(int *arr, int size) {
    int i, temp;

    temp = arr[size - 1];
    for (i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = temp;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int i, size;

    size = sizeof(arr) / sizeof(arr[0]);

    shift(arr, size);

    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
  
    return 0;
}