#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int heap[], int i, int size) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, largest, size);
    }
}

void buildMaxHeap(int heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, i, size);
    }
}

int* findSmallestIntegers(int arr[], int n, int k) {
    if (n <= 0 || k <= 0 || arr == NULL) {
        return NULL;
    }
    if (k > n) {
        k = n;
    }

    int *result = (int *)malloc(k * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        result[i] = arr[i];
    }

    buildMaxHeap(result, k);

    for (int i = k; i < n; i++) {
        if (arr[i] < result[0]) {
            result[0] = arr[i];
            maxHeapify(result, 0, k);
        }
    }

    return result;
}

int main() {
    int nums[] = {10, 4, 3, 20, 15, 6, 8, 2, 9};
    int n = sizeof(nums) / sizeof(nums[0]);
    int k = 4;

    int *smallest = findSmallestIntegers(nums, n, k);

    if (smallest != NULL) {
        for (int i = 0; i < k; i++) {
            printf("%d ", smallest[i]);
        }
        printf("\n");
        free(smallest);
        smallest = NULL;
    }

    return 0;
}