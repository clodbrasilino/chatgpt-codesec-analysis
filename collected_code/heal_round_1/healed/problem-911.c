#include <stdio.h>

void heapify(int arr[], int n, int i) {
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

void buildHeap(int arr[], int n) {
    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--)
        heapify(arr, n, i);
}

int maxProduct(int arr[], int n) {
    buildHeap(arr, n);

    int product = 1;

    for (int i = n - 1; i >= n - 3; i--)
        product *= arr[i];

    return product;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maxProduct(arr, n);
    printf("Maximum product of three numbers: %d\n", result);

    return 0;
}