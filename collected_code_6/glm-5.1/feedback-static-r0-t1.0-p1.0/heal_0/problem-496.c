#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(int *heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        min_heapify(heap, size, smallest);
    }
}

void build_min_heap(int *heap, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        min_heapify(heap, size, i);
}

int extract_min(int *heap, int *size) {
    if (*size <= 0) {
        return INT_MIN;
    }
    int min_val = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    min_heapify(heap, *size, 0);
    return min_val;
}

int *find_k_smallest(int *nums, int nums_size, int k, int *result_size) {
    if (nums == NULL || nums_size <= 0 || k <= 0) {
        *result_size = 0;
        return NULL;
    }

    if (k > nums_size) {
        k = nums_size;
    }

    int *heap = (int *)malloc(nums_size * sizeof(int));
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < nums_size; i++) {
        heap[i] = nums[i];
    }

    build_min_heap(heap, nums_size);

    int *result = (int *)malloc(k * sizeof(int));
    if (result == NULL) {
        free(heap);
        *result_size = 0;
        return NULL;
    }

    int current_size = nums_size;
    for (int i = 0; i < k; i++) {
        result[i] = extract_min(heap, &current_size);
    }

    free(heap);
    *result_size = k;
    return result;
}

int main() {
    int nums[] = {12, 3, 5, 7, 19, 1, 8, 15};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int k = 4;
    int result_size = 0;

    int *k_smallest = find_k_smallest(nums, nums_size, k, &result_size);

    if (k_smallest != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", k_smallest[i]);
        }
        printf("\n");
        free(k_smallest);
    }

    return 0;
}