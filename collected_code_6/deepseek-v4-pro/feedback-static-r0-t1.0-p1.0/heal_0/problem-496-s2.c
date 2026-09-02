#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

void min_heapify(int *heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        min_heapify(heap, size, smallest);
    }
}

void build_min_heap(int *heap, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        min_heapify(heap, size, i);
}

int extract_min(int *heap, int *size) {
    if (*size <= 0)
        return -1;

    int min = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    min_heapify(heap, *size, 0);
    return min;
}

void find_smallest_k(int *arr, int n, int k) {
    if (n <= 0 || k <= 0) {
        printf("Invalid input\n");
        return;
    }

    if (k > n)
        k = n;

    int *heap = (int *)malloc(n * sizeof(int));
    if (heap == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < n; i++)
        heap[i] = arr[i];

    build_min_heap(heap, n);

    int heap_size = n;
    int *result = (int *)malloc(k * sizeof(int));
    if (result == NULL) {
        free(heap);
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < k; i++)
        result[i] = extract_min(heap, &heap_size);

    printf("Smallest %d integers: ", k);
    for (int i = 0; i < k; i++)
        printf("%d ", result[i]);
    printf("\n");

    free(heap);
    free(result);
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 1, 8, 45, 23, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    find_smallest_k(arr, n, k);

    return 0;
}