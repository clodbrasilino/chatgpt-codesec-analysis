#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} SortedArray;

SortedArray* create_sorted_array(size_t initial_capacity) {
    SortedArray *sa = (SortedArray*)malloc(sizeof(SortedArray));
    sa->data = (int*)malloc(initial_capacity * sizeof(int));
    sa->size = 0;
    sa->capacity = initial_capacity;
    return sa;
}

void free_sorted_array(SortedArray *sa) {
    free(sa->data);
    free(sa);
}

void add_to_sorted_array(SortedArray *sa, int value) {
    if (sa->size == sa->capacity) {
        sa->capacity *= 2;
        sa->data = (int*)realloc(sa->data, sa->capacity * sizeof(int));
    }
    sa->data[sa->size++] = value;
}

typedef struct {
    int value;
    int index;
    int array_index;
} HeapNode;

typedef struct {
    HeapNode *data;
    size_t size;
    size_t capacity;
} MinHeap;

MinHeap* create_min_heap(size_t initial_capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(initial_capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = initial_capacity;
    return heap;
}

void free_min_heap(MinHeap *heap) {
    free(heap->data);
    free(heap);
}

void min_heap_push(MinHeap *heap, HeapNode node) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (HeapNode*)realloc(heap->data, heap->capacity * sizeof(HeapNode));
    }
    heap->data[heap->size] = node;
    int i = heap->size++;
    while (i > 0 && heap->data[(i - 1) / 2].value > heap->data[i].value) {
        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

HeapNode min_heap_pop(MinHeap *heap) {
    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < heap->size && heap->data[left].value < heap->data[smallest].value) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].value < heap->data[smallest].value) {
            smallest = right;
        }
        if (smallest == i) break;
        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        i = smallest;
    }
    return root;
}

/* Possible weaknesses found:
 *  Parameter 'heap' can be declared as pointer to const [constParameterPointer]
 */
int is_min_heap_empty(MinHeap *heap) {
    return heap->size == 0;
}

void merge_sorted_arrays(SortedArray **arrays, size_t num_arrays, SortedArray *result) {
    MinHeap *heap = create_min_heap(num_arrays);
    for (size_t i = 0; i < num_arrays; ++i) {
        if (arrays[i]->size > 0) {
            min_heap_push(heap, (HeapNode){.value = arrays[i]->data[0], .index = 0, .array_index = i});
        }
    }

    while (!is_min_heap_empty(heap)) {
        HeapNode node = min_heap_pop(heap);
        add_to_sorted_array(result, node.value);
        if (node.index + 1 < arrays[node.array_index]->size) {
            min_heap_push(heap, (HeapNode){.value = arrays[node.array_index]->data[node.index + 1], .index = node.index + 1, .array_index = node.array_index});
        }
    }

    free_min_heap(heap);
}

int main() {
    SortedArray *arrays[3];
    arrays[0] = create_sorted_array(5);
    arrays[1] = create_sorted_array(4);
    arrays[2] = create_sorted_array(3);

    add_to_sorted_array(arrays[0], 1);
    add_to_sorted_array(arrays[0], 4);
    add_to_sorted_array(arrays[0], 5);

    add_to_sorted_array(arrays[1], 2);
    add_to_sorted_array(arrays[1], 6);
    add_to_sorted_array(arrays[1], 7);

    add_to_sorted_array(arrays[2], 3);
    add_to_sorted_array(arrays[2], 8);
    add_to_sorted_array(arrays[2], 9);

    SortedArray *result = create_sorted_array(12);
    merge_sorted_arrays(arrays, 3, result);

    for (size_t i = 0; i < result->size; ++i) {
        printf("%d ", result->data[i]);
    }
    printf("\n");

    for (size_t i = 0; i < 3; ++i) {
        free_sorted_array(arrays[i]);
    }
    free_sorted_array(result);

    return 0;
}