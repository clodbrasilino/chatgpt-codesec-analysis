#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 1024

typedef struct {
    int *data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* create_max_heap(int capacity) {
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (!heap) return NULL;
    heap->data = (int*)malloc(sizeof(int) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(MaxHeap *heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

void heapify_up(MaxHeap *heap, int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && heap->data[index] > heap->data[parent]) {
        swap(&heap->data[index], &heap->data[parent]);
        heapify_up(heap, parent);
    }
}

int heap_push(MaxHeap *heap, int value) {
    if (heap->size >= heap->capacity) return -1;
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

int heap_pop(MaxHeap *heap, int *value) {
    if (heap->size <= 0) return -1;
    *value = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return 0;
}

void free_max_heap(MaxHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

int* find_largest_elements(const int *arr, int n, int k, int *result_size) {
    if (!arr || n <= 0 || k <= 0 || k > n || !result_size) return NULL;

    MaxHeap *heap = create_max_heap(n);
    if (!heap) return NULL;

    for (int i = 0; i < n; i++) {
        if (heap_push(heap, arr[i]) != 0) {
            free_max_heap(heap);
            return NULL;
        }
    }

    int *result = (int*)malloc(sizeof(int) * k);
    if (!result) {
        free_max_heap(heap);
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        if (heap_pop(heap, &result[i]) != 0) {
            free(result);
            free_max_heap(heap);
            return NULL;
        }
    }

    *result_size = k;
    free_max_heap(heap);
    return result;
}

int main(void) {
    int numbers[] = {42, 13, 7, 88, 25, 91, 3, 56, 74, 19};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int k = 4;
    int result_size = 0;

    int *largest = find_largest_elements(numbers, n, k, &result_size);
    if (!largest) {
        printf("Error finding largest elements\n");
        return 1;
    }

    printf("Largest %d integers: ", k);
    for (int i = 0; i < result_size; i++) {
        printf("%d ", largest[i]);
    }
    printf("\n");

    free(largest);
    return 0;
}