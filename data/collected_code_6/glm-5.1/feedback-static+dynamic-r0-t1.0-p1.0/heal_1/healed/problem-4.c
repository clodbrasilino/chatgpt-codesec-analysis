#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, n, largest);
    }
}

int *find_k_largest(const int *nums, int nums_size, int k, int *return_size) {
    *return_size = 0;
    if (nums == NULL || nums_size <= 0 || k <= 0)
        return NULL;

    if (k > nums_size)
        k = nums_size;

    int *result = (int *)malloc(k * sizeof(int));
    if (result == NULL)
        return NULL;

    int *heap = (int *)malloc(nums_size * sizeof(int));
    if (heap == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < nums_size; i++)
        heap[i] = nums[i];

    for (int i = nums_size / 2 - 1; i >= 0; i--)
        max_heapify(heap, nums_size, i);

    for (int i = 0; i < k; i++) {
        result[i] = heap[0];
        swap(&heap[0], &heap[nums_size - 1 - i]);
        max_heapify(heap, nums_size - 1 - i, 0);
        (*return_size)++;
    }

    free(heap);
    return result;
}

int main() {
    int nums[] = {3, 2, 1, 5, 6, 4};
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    int return_size;

    int *largest = find_k_largest(nums, nums_size, k, &return_size);

    if (largest != NULL && return_size > 0) {
        for (int i = 0; i < return_size; i++)
            printf("%d ", largest[i]);
        printf("\n");
        free(largest);
    }

    return 0;
}