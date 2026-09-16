#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(int *heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        min_heapify(heap, size, smallest);
    }
}

int* find_largest_integers(const int *nums, int num_size, int k) {
    if (nums == NULL || num_size <= 0 || k <= 0) {
        return NULL;
    }

    if (k > num_size) {
        k = num_size;
    }

    int *heap = (int *)malloc(k * sizeof(int));
    if (heap == NULL) {
        return NULL;
    }

    for (int i = 0; i < k; ++i) {
        heap[i] = nums[i];
    }

    for (int i = k / 2 - 1; i >= 0; --i) {
        min_heapify(heap, k, i);
    }

    for (int i = k; i < num_size; ++i) {
        if (nums[i] > heap[0]) {
            heap[0] = nums[i];
            min_heapify(heap, k, 0);
        }
    }

    return heap;
}

int main(void) {
    int nums[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int num_size = sizeof(nums) / sizeof(nums[0]);
    int k = 3;

    if (k > num_size) {
        k = num_size;
    }

    int *largest_nums = find_largest_integers(nums, num_size, k);
    if (largest_nums == NULL) {
        fprintf(stderr, "Failed to find largest integers.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < k; ++i) {
        printf("%d ", largest_nums[i]);
    }
    printf("\n");

    free(largest_nums);
    return EXIT_SUCCESS;
}