#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_init(MinHeap *heap, size_t capacity)
{
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

static void heap_free(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static void heapify_up(MinHeap *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] <= heap->data[index]) {
            break;
        }
        swap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

static void heapify_down(MinHeap *heap, size_t index)
{
    while (index < heap->size) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

static int heap_push(MinHeap *heap, int value)
{
    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

static int heap_pop(MinHeap *heap, int *value)
{
    if (heap == NULL || heap->size == 0 || value == NULL) {
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

static int heap_peek(const MinHeap *heap, int *value)
{
    if (heap == NULL || heap->size == 0 || value == NULL) {
        return -1;
    }
    *value = heap->data[0];
    return 0;
}

int find_largest_k(const int *arr, size_t n, size_t k, int *result)
{
    if (arr == NULL || result == NULL || k == 0 || k > n) {
        return -1;
    }

    MinHeap heap;
    if (heap_init(&heap, k) != 0) {
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        if (heap.size < k) {
            if (heap_push(&heap, arr[i]) != 0) {
                heap_free(&heap);
                return -1;
            }
        } else {
            int top;
            if (heap_peek(&heap, &top) != 0) {
                heap_free(&heap);
                return -1;
            }
            if (arr[i] > top) {
                if (heap_pop(&heap, &top) != 0) {
                    heap_free(&heap);
                    return -1;
                }
                if (heap_push(&heap, arr[i]) != 0) {
                    heap_free(&heap);
                    return -1;
                }
            }
        }
    }

    for (size_t i = 0; i < k; i++) {
        if (heap_pop(&heap, &result[k - 1 - i]) != 0) {
            heap_free(&heap);
            return -1;
        }
    }

    heap_free(&heap);
    return 0;
}

int main(void)
{
    int numbers[] = {3, 2, 1, 5, 6, 4, 9, 7, 8};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);
    size_t k = 3;

    int *result = malloc(k * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_largest_k(numbers, n, k, result) != 0) {
        fprintf(stderr, "Failed to find largest elements\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Largest %zu integers: ", k);
    for (size_t i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}