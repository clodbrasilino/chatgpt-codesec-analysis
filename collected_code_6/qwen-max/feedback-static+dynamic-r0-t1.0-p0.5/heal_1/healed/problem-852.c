#include <stdio.h>
#include <stdlib.h>

int* remove_negatives(int *arr, int n, int *new_size) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 0) {
            arr[count++] = arr[i];
        }
    }
    *new_size = count;
    return arr;
}

int main() {
    int arr[] = {-1, 2, -3, 4, -5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int new_size;

    const int *result = remove_negatives(arr, n, &new_size);

    for (int i = 0; i < new_size; ++i) {
        printf("%d ", result[i]);
    }

    return 0;
}