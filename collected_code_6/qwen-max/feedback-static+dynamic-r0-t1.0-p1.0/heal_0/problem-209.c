#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void deleteRootAndInsert(int *arr, int *n, int value) {
    if (*n == 0) return;

    int deleted = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapify(arr, *n, 0);

    insertIntoHeap(arr, n, value);
}

void insertIntoHeap(int *arr, int *n, int value) {
    (*n)++;
    int i = *n - 1;
    while (i > 0 && arr[(i - 1) / 2] < value) {
        arr[i] = arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    arr[i] = value;
}

int main() {
    int arr[] = {10, 5, 3, 2, 4};
    int n = 5;
    int new_value = 15;

    deleteRootAndInsert(arr, &n, new_value);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}