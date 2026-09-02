#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
} Tuple;

typedef struct {
    Tuple *data;
    int size;
    int capacity;
} MinHeap;

static void heap_init(MinHeap *heap, int capacity) {
    heap->data = (Tuple *)malloc(sizeof(Tuple) * capacity);
    if (!heap->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    heap->size = 0;
    heap->capacity = capacity;
}

static void heap_free(MinHeap *heap) {
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void heap_swap(Tuple *a, Tuple *b) {
    Tuple temp = *a;
    *a = *b;
    *b = temp;
}

static void heap_sift_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[parent].value < heap->data[index].value) {
            heap_swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        } else {
            break;
        }
    }
}

static void heap_sift_down(MinHeap *heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap->size && heap->data[left].value > heap->data[largest].value) {
            largest = left;
        }
        if (right < heap->size && heap->data[right].value > heap->data[largest].value) {
            largest = right;
        }

        if (largest != index) {
            heap_swap(&heap->data[index], &heap->data[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

static void heap_push(MinHeap *heap, Tuple item) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = item;
        heap_sift_up(heap, heap->size);
        heap->size++;
    } else if (item.value < heap->data[0].value) {
        heap->data[0] = item;
        heap_sift_down(heap, 0);
    }
}

static int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->value < tb->value) return -1;
    if (ta->value > tb->value) return 1;
    return ta->id - tb->id;
}

int find_min_k_records(const Tuple *tuples, int n, int k, Tuple *result) {
    if (!tuples || n <= 0 || k <= 0 || !result) {
        return -1;
    }

    if (k > n) {
        k = n;
    }

    MinHeap heap;
    heap_init(&heap, k);

    for (int i = 0; i < n; i++) {
        heap_push(&heap, tuples[i]);
    }

    for (int i = 0; i < heap.size; i++) {
        result[i] = heap.data[i];
    }

    qsort(result, heap.size, sizeof(Tuple), compare_tuples);

    heap_free(&heap);
    return heap.size > 0 ? heap.size : k;
}

int main(void) {
    Tuple tuples[] = {
        {1, 3.5}, {2, 1.2}, {3, 4.8}, {4, 0.9},
        {5, 2.7}, {6, 1.5}, {7, 3.1}, {8, 1.2}
    };
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int k = 4;
    Tuple result[4];

    int count = find_min_k_records(tuples, n, k, result);

    printf("Minimum %d records:\n", count);
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Value: %.2f\n", result[i].id, result[i].value);
    }

    return 0;
}