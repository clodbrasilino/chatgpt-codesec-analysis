#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t used;
    size_t size;
} Heap;

typedef int (*Compare)(const void *, const void *);

Heap *create_heap(size_t capacity) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    if (heap == NULL) return NULL;
    heap->array = (int *)malloc(capacity * sizeof(int));
    if (heap->array == NULL) {
        free(heap);
        return NULL;
    }
    heap->used = 0;
    heap->size = capacity;
    return heap;
}

void destroy_heap(Heap *heap) {
    if (heap) {
        free(heap->array);
        free(heap);
    }
}

void sift_up(Heap *heap, size_t index, Compare cmp) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (cmp(&heap->array[index], &heap->array[parent]) < 0) {
            int temp = heap->array[index];
            heap->array[index] = heap->array[parent];
            heap->array[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}

void sift_down(Heap *heap, size_t index, Compare cmp) {
    size_t left, right, smallest;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;
        if (left < heap->used && cmp(&heap->array[left], &heap->array[smallest]) < 0) {
            smallest = left;
        }
        if (right < heap->used && cmp(&heap->array[right], &heap->array[smallest]) < 0) {
            smallest = right;
        }
        if (smallest != index) {
            int temp = heap->array[index];
            heap->array[index] = heap->array[smallest];
            heap->array[smallest] = temp;
            index = smallest;
        } else {
            break;
        }
    }
}

int heap_push(Heap *heap, int value, Compare cmp) {
    if (heap->used >= heap->size) return -1;
    heap->array[heap->used++] = value;
    sift_up(heap, heap->used - 1, cmp);
    return 0;
}

int heap_pop(Heap *heap, int *value, Compare cmp) {
    if (heap->used == 0) return -1;
    *value = heap->array[0];
    heap->array[0] = heap->array[--heap->used];
    sift_down(heap, 0, cmp);
    return 0;
}

int compare_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int *merge_sorted_arrays(int **arrays, size_t *sizes, size_t count, size_t *result_size) {
    *result_size = 0;
    for (size_t i = 0; i < count; ++i) {
        *result_size += sizes[i];
    }

    int *result = (int *)malloc(*result_size * sizeof(int));
    if (result == NULL) return NULL;

    Heap *heap = create_heap(count);
    if (heap == NULL) {
        free(result);
        return NULL;
    }

    size_t *indices = (size_t *)calloc(count, sizeof(size_t));
    if (indices == NULL) {
        free(result);
        destroy_heap(heap);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (sizes[i] > 0) {
            heap_push(heap, arrays[i][0], compare_int);
        }
    }

    size_t result_index = 0;
    while (heap->used > 0) {
        int min_value;
        heap_pop(heap, &min_value, compare_int);

        result[result_index++] = min_value;

        for (size_t i = 0; i < count; ++i) {
            if (arrays[i][indices[i]] == min_value) {
                indices[i]++;
                if (indices[i] < sizes[i]) {
                    heap_push(heap, arrays[i][indices[i]], compare_int);
                }
                break;
            }
        }
    }

    free(indices);
    destroy_heap(heap);
    return result;
}

int main() {
    int arr1[] = {1, 4, 5};
    int arr2[] = {1, 3, 4};
    int arr3[] = {2, 6};

    int *arrays[] = {arr1, arr2, arr3};
    size_t sizes[] = {3, 3, 2};
    size_t count = 3;

    size_t result_size;
    int *result = merge_sorted_arrays(arrays, sizes, count, &result_size);

    if (result) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    }

    return 0;
}