#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Heap;

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_init(Heap *heap, size_t capacity) {
    if (heap == NULL || capacity == 0) {
        return -1;
    }
    heap->data = malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void heap_free(Heap *heap) {
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static void heapify_down(Heap *heap, size_t idx) {
    size_t smallest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

static void heapify_up(Heap *heap, size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap->data[parent] <= heap->data[idx]) {
            break;
        }
        swap(&heap->data[parent], &heap->data[idx]);
        idx = parent;
    }
}

static int heap_push(Heap *heap, int value) {
    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

static int heap_pop(Heap *heap, int *value) {
    if (heap == NULL || value == NULL || heap->size == 0) {
        return -1;
    }
    *value = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        heapify_down(heap, 0);
    }
    return 0;
}

static int heap_peek(const Heap *heap, int *value) {
    if (heap == NULL || value == NULL || heap->size == 0) {
        return -1;
    }
    *value = heap->data[0];
    return 0;
}

int get_n_largest(const int *dataset, size_t dataset_size, size_t n, int *result) {
    Heap heap;
    size_t i;
    size_t result_count;

    if (dataset == NULL || result == NULL || n == 0) {
        return -1;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    if (heap_init(&heap, n) != 0) {
        return -1;
    }

    for (i = 0; i < dataset_size; i++) {
        if (heap.size < n) {
            if (heap_push(&heap, dataset[i]) != 0) {
                heap_free(&heap);
                return -1;
            }
        } else {
            int min_val;
            if (heap_peek(&heap, &min_val) != 0) {
                heap_free(&heap);
                return -1;
            }
            if (dataset[i] > min_val) {
                int dummy;
                if (heap_pop(&heap, &dummy) != 0) {
                    heap_free(&heap);
                    return -1;
                }
                if (heap_push(&heap, dataset[i]) != 0) {
                    heap_free(&heap);
                    return -1;
                }
            }
        }
    }

    result_count = heap.size;
    for (i = 0; i < result_count; i++) {
        if (heap_pop(&heap, &result[result_count - 1 - i]) != 0) {
            heap_free(&heap);
            return -1;
        }
    }

    heap_free(&heap);
    return (int)result_count;
}

int main(void) {
    int dataset[] = {5, 12, 3, 8, 20, 1, 15, 7, 25, 10};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    int *result;
    int count;
    int i;

    result = malloc(n * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    count = get_n_largest(dataset, dataset_size, n, result);
    if (count < 0) {
        fprintf(stderr, "Failed to get largest items\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Top %d largest items: ", count);
    for (i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}