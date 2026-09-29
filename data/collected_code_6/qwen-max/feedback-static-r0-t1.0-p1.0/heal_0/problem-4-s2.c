#include <stdio.h>
#include <stdlib.h>

#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

void maxHeapify(int* arr, int n, int i) {
    int largest = i;
    int l = LEFT(i);
    int r = RIGHT(i);

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

int findLargest(int* arr, int n) {
    if (n == 0)
        return -1;

    buildMaxHeap(arr, n);
    return arr[0];
}

int main() {
    int numbers[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int largest = findLargest(numbers, n);
    printf("The largest number is: %d\n", largest);
    return 0;
}