#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(int *heap, int heap_size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && heap[left] < heap[smallest]) {
        smallest = left;
    }

    if (right < heap_size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        min_heapify(heap, heap_size, smallest);
    }
}

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
int* find_k_smallest(int *nums, int nums_size, int k, int *result_size) {
    if (nums_size <= 0 || k <= 0) {
        *result_size = 0;
        return NULL;
    }

    if (k > nums_size) {
        k = nums_size;
    }

    int *heap = (int*)malloc(nums_size * sizeof(int));
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < nums_size; i++) {
        heap[i] = nums[i];
    }

    for (int i = nums_size / 2 - 1; i >= 0; i--) {
        min_heapify(heap, nums_size, i);
    }

    int *result = (int*)malloc(k * sizeof(int));
    if (result == NULL) {
        free(heap);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        result[i] = heap[0];
        heap[0] = heap[nums_size - 1 - i];
        min_heapify(heap, nums_size - 1 - i, 0);
    }

    free(heap);
    *result_size = k;
    return result;
}

int main() {
    int nums[] = {12, 3, 5, 7, 19, 1, 8, 15, 6, 2};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int k = 4;
    int result_size = 0;

    int *smallest = find_k_smallest(nums, nums_size, k, &result_size);

    if (smallest != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", smallest[i]);
        }
        printf("\n");
        free(smallest);
    }

    return 0;
}