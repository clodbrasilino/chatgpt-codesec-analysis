#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 3

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void buildHeap(int arr[], int n) {
    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int maxProduct(int arr[], int n) {
    buildHeap(arr, n);

    return arr[0] * arr[1] * arr[2];
}

int main() {
    int arr[] = {1, 10, 2, 6, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Maximum product is %d\n", maxProduct(arr, n));

    return 0;
}