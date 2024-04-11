#include <stdio.h>
#include <stdlib.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

void printArray(int arr[], int size) {
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void printSmallest(int arr[], int n, int k) {
    selectionSort(arr, n);
    for (int i=0; i<k; i++)
        printf("%d ", arr[i]);
}

int main() {
    int arr[] = {12, 23, 10, 34, 20, 50, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 3;
    printSmallest(arr, n, k);
    return 0;
}