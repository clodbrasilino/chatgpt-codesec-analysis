#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify_up(MinHeap *heap, size_t index)
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

void min_heapify_down(MinHeap *heap, size_t index)
{
    while (1) {
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

int min_heap_init(MinHeap *heap, size_t capacity)
{
    if (capacity == 0) {
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

void min_heap_free(MinHeap *heap)
{
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

int min_heap_insert(MinHeap *heap, int value)
{
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = value;
    min_heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

int min_heap_peek(const MinHeap *heap, int *value)
{
    if (heap->size == 0 || value == NULL) {
        return -1;
    }
    *value = heap->data[0];
    return 0;
}

int min_heap_replace_root(MinHeap *heap, int value)
{
    if (heap->size == 0) {
        return -1;
    }
    heap->data[0] = value;
    min_heapify_down(heap, 0);
    return 0;
}

int min_heap_extract_min(MinHeap *heap, int *value)
{
    if (heap->size == 0 || value == NULL) {
        return -1;
    }
    *value = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        min_heapify_down(heap, 0);
    }
    return 0;
}

int find_largest_k(const int *arr, size_t n, size_t k, int *result)
{
    MinHeap heap;
    size_t i;

    if (arr == NULL || result == NULL || k == 0 || k > n) {
        return -1;
    }

    if (min_heap_init(&heap, k) != 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (heap.size < k) {
            if (min_heap_insert(&heap, arr[i]) != 0) {
                min_heap_free(&heap);
                return -1;
            }
        } else {
            int min_val;
            if (min_heap_peek(&heap, &min_val) != 0) {
                min_heap_free(&heap);
                return -1;
            }
            if (arr[i] > min_val) {
                if (min_heap_replace_root(&heap, arr[i]) != 0) {
                    min_heap_free(&heap);
                    return -1;
                }
            }
        }
    }

    for (i = 0; i < k; i++) {
        if (min_heap_extract_min(&heap, &result[i]) != 0) {
            min_heap_free(&heap);
            return -1;
        }
    }

    min_heap_free(&heap);
    return 0;
}

int main(void)
{
    int numbers[] = {3, 2, 1, 5, 6, 4, 9, 8, 7};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);
    size_t k;
    int *result;
    size_t i;

    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (k > n || k == 0) {
        fprintf(stderr, "Error: k cannot be larger than array size or zero\n");
        return EXIT_FAILURE;
    }

    result = malloc(k * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_largest_k(numbers, n, k, result) != 0) {
        fprintf(stderr, "Error: failed to find largest elements\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("The %zu largest integers are: ", k);
    for (i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}