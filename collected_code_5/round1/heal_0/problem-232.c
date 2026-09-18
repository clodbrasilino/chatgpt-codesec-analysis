#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, max_idx;

    for (i = 0; i < n-1; i++) {
        max_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] > arr[max_idx])
                max_idx = j;
        swap(&arr[max_idx], &arr[i]);
    }
}

void getNLargest(int arr[], int arr_size, int n) {
    if (n <= 0 || n > arr_size) {
        printf("Invalid 'n' value provided.\n");
        return;
    }

    selectionSort(arr, arr_size);

    for (int i = 0 ; i < n ; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int dataset[] = {32, 45, 23, 67, 11, 89, 9, 21};
    int size = sizeof(dataset) / sizeof(dataset[0]);

    int n = 3;
    getNLargest(dataset, size, n);

    return 0;
}