#include <stdio.h>
#include <stdlib.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
        }
    }
}

void printKMaxMin(int arr[], int n, int k) {
    bubbleSort(arr, n);
    printf("Minimum %d elements: ", k);
    for (int i = 0; i < k; i++)
        printf("%d ", arr[i]);
    printf("\nMaximum %d elements: ", k);
    for (int i = n-k; i < n; i++)
        printf("%d ", arr[i]);
}

int main() {
    int arr[] = {10, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 3;
    printKMaxMin(arr, n, k);
    return 0;
}