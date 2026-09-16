#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int *heap, int size, int i) {
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
        maxHeapify(heap, size, largest);
    }
}

int* findKLargest(const int *nums, int numsSize, int k) {
    if (numsSize <= 0 || k <= 0 || k > numsSize) {
        return NULL;
    }

    int *result = (int*)malloc(k * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    int *heap = (int*)malloc(numsSize * sizeof(int));
    if (heap == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < numsSize; i++) {
        heap[i] = nums[i];
    }

    for (int i = numsSize / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, numsSize, i);
    }

    for (int i = 0; i < k; i++) {
        result[i] = heap[0];
        heap[0] = heap[numsSize - 1 - i];
        maxHeapify(heap, numsSize - 1 - i, 0);
    }

    free(heap);
    return result;
}

int main() {
    int nums[] = {3, 2, 1, 5, 6, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;

    int *largest = findKLargest(nums, numsSize, k);
    if (largest == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < k; i++) {
        printf("%d ", largest[i]);
    }
    printf("\n");

    free(largest);
    return EXIT_SUCCESS;
}