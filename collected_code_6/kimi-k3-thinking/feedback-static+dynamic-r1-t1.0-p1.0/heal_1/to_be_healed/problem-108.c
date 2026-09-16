#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int value;
    size_t array_index;
    size_t element_index;
} HeapNode;

typedef struct {
    HeapNode *heap;
    size_t heap_size;
    size_t heap_capacity;
    const int **arrays;
    const size_t *array_sizes;
    size_t num_arrays;
} MergeIterator;

static void swap_nodes(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(HeapNode *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap[parent].value <= heap[index].value) {
            break;
        }
        swap_nodes(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void heapify_down(HeapNode *heap, size_t size, size_t index)
{
    for (;;) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;

        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap_nodes(&heap[smallest], &heap[index]);
        index = smallest;
    }
}

static bool heap_push(MergeIterator *it, HeapNode node)
{
    if (it->heap_size == it->heap_capacity) {
        size_t new_capacity = (it->heap_capacity == 0) ? 8 : it->heap_capacity * 2;
        HeapNode *new_heap = realloc(it->heap, new_capacity * sizeof(*new_heap));
        if (new_heap == NULL) {
            return false;
        }
        it->heap = new_heap;
        it->heap_capacity = new_capacity;
    }
    it->heap[it->heap_size] = node;
    heapify_up(it->heap, it->heap_size);
    it->heap_size++;
    return true;
}

static bool heap_pop(MergeIterator *it, HeapNode *out)
{
    if (it->heap_size == 0) {
        return false;
    }
    *out = it->heap[0];
    it->heap_size--;
    if (it->heap_size > 0) {
        it->heap[0] = it->heap[it->heap_size];
        heapify_down(it->heap, it->heap_size, 0);
    }
    return true;
}

MergeIterator *merge_iterator_create(const int **arrays, const size_t *array_sizes, size_t num_arrays)
{
    if (arrays == NULL || array_sizes == NULL) {
        return NULL;
    }

    MergeIterator *it = malloc(sizeof(*it));
    if (it == NULL) {
        return NULL;
    }

    it->heap = NULL;
    it->heap_size = 0;
    it->heap_capacity = 0;
    it->arrays = arrays;
    it->array_sizes = array_sizes;
    it->num_arrays = num_arrays;

    if (num_arrays > 0) {
        it->heap = malloc(num_arrays * sizeof(*it->heap));
        if (it->heap == NULL) {
            free(it);
            return NULL;
        }
        it->heap_capacity = num_arrays;
    }

    for (size_t i = 0; i < num_arrays; i++) {
        if (arrays[i] != NULL && array_sizes[i] > 0) {
            HeapNode node;
            node.value = arrays[i][0];
            node.array_index = i;
            node.element_index = 0;
            it->heap[it->heap_size] = node;
            heapify_up(it->heap, it->heap_size);
            it->heap_size++;
        }
    }

    return it;
}

bool merge_iterator_next(MergeIterator *it, int *out_value)
{
    if (it == NULL || out_value == NULL) {
        return false;
    }

    HeapNode node;
    if (!heap_pop(it, &node)) {
        return false;
    }

    *out_value = node.value;

    size_t next_index = node.element_index + 1;
    if (next_index < it->array_sizes[node.array_index]) {
        HeapNode next_node;
        next_node.value = it->arrays[node.array_index][next_index];
        next_node.array_index = node.array_index;
        next_node.element_index = next_index;
        if (!heap_push(it, next_node)) {
            return false;
        }
    }

    return true;
}

void merge_iterator_destroy(MergeIterator *it)
{
    if (it != NULL) {
        free(it->heap);
        free(it);
    }
}

int main(void)
{
    int a[] = {1, 4, 7, 10};
    int b[] = {2, 5, 8};
    int c[] = {3, 6, 9, 12, 15};
    int d[] = {0, 11};

    const int *arrays[] = {a, b, c, d};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    size_t sizes[] = {4, 3, 5, 2};
    size_t num_arrays = sizeof(arrays) / sizeof(arrays[0]);

    MergeIterator *it = merge_iterator_create(arrays, sizes, num_arrays);
    if (it == NULL) {
        fprintf(stderr, "Failed to create merge iterator\n");
        return EXIT_FAILURE;
    }

    int value;
    while (merge_iterator_next(it, &value)) {
        printf("%d ", value);
    }
    printf("\n");

    merge_iterator_destroy(it);
    return EXIT_SUCCESS;
}