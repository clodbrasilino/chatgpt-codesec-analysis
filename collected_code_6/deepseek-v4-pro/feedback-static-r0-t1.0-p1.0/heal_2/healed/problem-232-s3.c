#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MaxHeap;

static void heap_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MaxHeap *heap, size_t index) {
    size_t largest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    if (largest != index) {
        heap_swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

static void heapify_up(MaxHeap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[index] > heap->data[parent]) {
            heap_swap(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

static MaxHeap *max_heap_create(size_t capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    if (heap == NULL) {
        return NULL;
    }

    heap->data = (int *)malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void max_heap_destroy(MaxHeap *heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

static int max_heap_push(MaxHeap *heap, int value) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = value;
        heapify_up(heap, heap->size);
        heap->size++;
        return 0;
    }

    if (value < heap->data[0]) {
        heap->data[0] = value;
        heapify_down(heap, 0);
        return 0;
    }

    return -1;
}

int *find_n_largest(const int *dataset, size_t data_size, size_t n, size_t *result_size) {
    if (dataset == NULL || result_size == NULL || n == 0 || data_size == 0 || n > data_size) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    MaxHeap *heap = max_heap_create(n);
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < data_size; i++) {
        max_heap_push(heap, dataset[i]);
    }

    *result_size = heap->size;
    int *result = (int *)malloc(heap->size * sizeof(int));
    if (result == NULL) {
        max_heap_destroy(heap);
        *result_size = 0;
        return NULL;
    }

    memcpy(result, heap->data, heap->size * sizeof(int));
    max_heap_destroy(heap);
    return result;
}

int main(void) {
    int dataset[] = {12, 45, 1, 78, 90, 33, 7, 65, 22, 89, 100, 54};
    size_t data_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 5;
    size_t result_size = 0;

    int *result = find_n_largest(dataset, data_size, n, &result_size);

    if (result != NULL) {
        printf("The %zu largest items are: ", result_size);
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Failed to find the largest items.\n");
    }

    return 0;
}