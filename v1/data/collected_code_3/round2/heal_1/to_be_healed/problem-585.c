#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'heap' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

void insert(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        if (value <= heap->data[0])
            return;

        heap->data[0] = value;
        heapify(heap, 0);
    } else {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*heap.data + (long unsigned int)*heap.size * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        heap->data[heap->size++] = value;

        for (int i = heap->size / 2 - 1; i >= 0; i--)
            heapify(heap, i);
    }
}

void findNExpensiveItems(int* prices, int n, int size) {
    Heap* heap = createHeap(n);

    for (int i = 0; i < size; i++)
        insert(heap, prices[i]);

    printf("The %d most expensive items are: ", n);
    for (int i = 0; i < n; i++)
        printf("%d ", heap->data[i]);
    printf("\n");

    free(heap->data);
    free(heap);
}

int main() {
    int prices[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 5;
    int size = sizeof(prices) / sizeof(prices[0]);

    findNExpensiveItems(prices, n, size);

    return 0;
}