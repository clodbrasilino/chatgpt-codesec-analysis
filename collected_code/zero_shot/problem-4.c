#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--)
        heapify(arr, n, i);
}

void heapQueue(int arr[], int n, int k) {
    buildHeap(arr, n);

    for (int i = n - 1; i >= n - k; i--) {
        printf("%d ", arr[0]);
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {10, 7, 15, 20, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    heapQueue(arr, n, k);

    return 0;
}
