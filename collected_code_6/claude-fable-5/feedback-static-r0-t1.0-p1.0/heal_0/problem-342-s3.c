#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int listIndex;
    int elemIndex;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    size_t size;
    size_t capacity;
} MinHeap;

static MinHeap *heap_create(size_t capacity)
{
    MinHeap *heap;

    if (capacity == 0U) {
        return NULL;
    }
    heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (heap == NULL) {
        return NULL;
    }
    heap->nodes = (HeapNode *)malloc(capacity * sizeof(HeapNode));
    if (heap->nodes == NULL) {
        free(heap);
        return NULL;
    }
    heap->size = 0U;
    heap->capacity = capacity;
    return heap;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->nodes);
        free(heap);
    }
}

static void heap_swap(HeapNode *a, HeapNode *b)
{
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static int heap_push(MinHeap *heap, HeapNode node)
{
    size_t i;

    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->nodes[heap->size] = node;
    i = heap->size;
    heap->size++;
    while (i > 0U) {
        size_t parent = (i - 1U) / 2U;
        if (heap->nodes[parent].value > heap->nodes[i].value) {
            heap_swap(&heap->nodes[parent], &heap->nodes[i]);
            i = parent;
        } else {
            break;
        }
    }
    return 0;
}

static int heap_pop(MinHeap *heap, HeapNode *out)
{
    size_t i;

    if (heap == NULL || heap->size == 0U || out == NULL) {
        return -1;
    }
    *out = heap->nodes[0];
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    i = 0U;
    for (;;) {
        size_t left = (2U * i) + 1U;
        size_t right = (2U * i) + 2U;
        size_t smallest = i;

        if (left < heap->size &&
            heap->nodes[left].value < heap->nodes[smallest].value) {
            smallest = left;
        }
        if (right < heap->size &&
            heap->nodes[right].value < heap->nodes[smallest].value) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        heap_swap(&heap->nodes[i], &heap->nodes[smallest]);
        i = smallest;
    }
    return 0;
}

int findSmallestRange(const int *const *arrays, const int *sizes, int k,
                      int *rangeStart, int *rangeEnd)
{
    MinHeap *heap;
    int currentMax;
    int bestStart;
    int bestEnd;
    long bestWidth;
    int i;
    int status;

    if (arrays == NULL || sizes == NULL || rangeStart == NULL ||
        rangeEnd == NULL || k <= 0) {
        return -1;
    }
    for (i = 0; i < k; i++) {
        if (arrays[i] == NULL || sizes[i] <= 0) {
            return -1;
        }
    }
    heap = heap_create((size_t)k);
    if (heap == NULL) {
        return -1;
    }
    currentMax = INT_MIN;
    for (i = 0; i < k; i++) {
        HeapNode node;
        node.value = arrays[i][0];
        node.listIndex = i;
        node.elemIndex = 0;
        if (heap_push(heap, node) != 0) {
            heap_destroy(heap);
            return -1;
        }
        if (arrays[i][0] > currentMax) {
            currentMax = arrays[i][0];
        }
    }
    bestStart = 0;
    bestEnd = 0;
    bestWidth = LONG_MAX;
    status = 0;
    for (;;) {
        HeapNode minNode;
        long width;

        if (heap_pop(heap, &minNode) != 0) {
            status = -1;
            break;
        }
        width = (long)currentMax - (long)minNode.value;
        if (width < bestWidth) {
            bestWidth = width;
            bestStart = minNode.value;
            bestEnd = currentMax;
        }
        if (minNode.elemIndex + 1 >= sizes[minNode.listIndex]) {
            break;
        }
        minNode.elemIndex++;
        minNode.value = arrays[minNode.listIndex][minNode.elemIndex];
        if (minNode.value > currentMax) {
            currentMax = minNode.value;
        }
        if (heap_push(heap, minNode) != 0) {
            status = -1;
            break;
        }
    }
    heap_destroy(heap);
    if (status == 0) {
        *rangeStart = bestStart;
        *rangeEnd = bestEnd;
    }
    return status;
}

int main(void)
{
    int arr1[] = {4, 10, 15, 24, 26};
    int arr2[] = {0, 9, 12, 20};
    int arr3[] = {5, 18, 22, 30};
    const int *arrays[3];
    int sizes[3];
    int rangeStart;
    int rangeEnd;

    arrays[0] = arr1;
    arrays[1] = arr2;
    arrays[2] = arr3;
    sizes[0] = (int)(sizeof(arr1) / sizeof(arr1[0]));
    sizes[1] = (int)(sizeof(arr2) / sizeof(arr2[0]));
    sizes[2] = (int)(sizeof(arr3) / sizeof(arr3[0]));

    if (findSmallestRange(arrays, sizes, 3, &rangeStart, &rangeEnd) != 0) {
        if (fprintf(stderr, "Failed to compute smallest range\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    if (printf("Smallest range: [%d, %d]\n", rangeStart, rangeEnd) < 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}