#include <stdio.h>
#include <stdlib.h>

void interchange(int *arr, int size) {
    if (size > 1) {
        int temp = arr[0];
        arr[0] = arr[size - 1];
        arr[size - 1] = temp;
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    interchange(arr, size);

    printf("\nArray after interchanging first and last: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}