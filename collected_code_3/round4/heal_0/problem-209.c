#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

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

void deleteRoot(int arr[], int *n) {
    int lastElement = arr[*n - 1];
    arr[0] = lastElement;
    *n = *n - 1;
    heapify(arr, *n, 0);
}

void insertKey(int arr[], int *n, int key) {
    if (*n == MAX_SIZE) {
        printf("\nOverflow: Could not insert Key\n");
        return;
    }

    arr[*n] = key;
    *n = *n + 1;

    for (int i = *n / 2 - 1; i >= 0; i--)
        heapify(arr, *n, i);
}

int main() {
    int arr[MAX_SIZE] = {10, 5, 3, 2, 4};
    int n = 5;

    deleteRoot(arr, &n);
    insertKey(arr, &n, 15);

    printf("Modified heap is \n");
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}