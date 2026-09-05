#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int *heap, int heap_size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && heap[left] > heap[largest])
        largest = left;

    if (right < heap_size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        max_heapify(heap, heap_size, largest);
    }
}

void build_max_heap(int *heap, int heap_size) {
    for (int i = heap_size / 2 - 1; i >= 0; i--)
        max_heapify(heap, heap_size, i);
}

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
int *find_largest_integers(int *nums, int nums_size, int k, int *result_size) {
    if (nums_size <= 0 || k <= 0) {
        *result_size = 0;
        return NULL;
    }

    if (k > nums_size)
        k = nums_size;

    int *heap = (int *)malloc(nums_size * sizeof(int));
    if (!heap) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < nums_size; i++)
        heap[i] = nums[i];

    build_max_heap(heap, nums_size);

    int *result = (int *)malloc(k * sizeof(int));
    if (!result) {
        free(heap);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        result[i] = heap[0];
        heap[0] = heap[nums_size - 1 - i];
        max_heapify(heap, nums_size - 1 - i, 0);
    }

    free(heap);
    *result_size = k;
    return result;
}

int main() {
    int nums[] = {3, 2, 1, 5, 6, 4};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    int result_size;

    int *largest = find_largest_integers(nums, nums_size, k, &result_size);

    if (largest) {
        for (int i = 0; i < result_size; i++)
            printf("%d ", largest[i]);
        printf("\n");
        free(largest);
    }

    return 0;
}