#include <stdio.h>
#include <stdlib.h>

int findKthElement(int* arr, int size, int k) {
    if (arr == NULL || size <= 0 || k < 0 || k >= size) {
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }
    return arr[k];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    printf("The kth element is %d\n", findKthElement(arr, size, k));
    return 0;
}