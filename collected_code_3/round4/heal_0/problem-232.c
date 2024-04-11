#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
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

void printNLargest(int arr[], int arr_size, int n) {
    selectionSort(arr, arr_size);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

int main() {
    int arr[] = {12, 13, 1, 10, 34, 1};
    int n = 3;
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    printNLargest(arr, arr_size, n);
    return 0;
}