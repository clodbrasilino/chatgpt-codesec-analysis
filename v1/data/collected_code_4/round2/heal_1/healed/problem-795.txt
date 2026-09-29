#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int count;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    if(heap == NULL) {
        return NULL;
    }
    heap->data = (int*) malloc(capacity * sizeof(int));
    if(heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->count = 0;
    heap->capacity = capacity;
    return heap;
}

void insertHeap(Heap *heap, int value) {
    if (heap->count == heap->capacity) {
        heap->capacity *= 2;
        int* new_data = (int*) realloc(heap->data, heap->capacity * sizeof(int));
        if(new_data == NULL) {
            return;
        }
        heap->data = new_data;
    }

    int i = heap->count++;
    while (i && value < heap->data[(i - 1) / 2]) {
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->data[i] = value;
}

int removeHeap(Heap *heap) {
    if (!heap->count) {
        return -1;
    }

    int value = heap->data[0];
    heap->data[0] = heap->data[--heap->count];

    int i = 0, j = 1;
    while (j < heap->count) {
        if (j + 1 < heap->count && heap->data[j] > heap->data[j + 1]) {
            j++;
        }

        if (heap->data[i] <= heap->data[j]) {
            break;
        }

        int tmp = heap->data[i];
        heap->data[i] = heap->data[j];
        heap->data[j] = tmp;

        i = j;
        j = 2 * i + 1;
    }

    return value;
}

int* cheapItems(Heap *heap, int n) {
    int *items = (int*) malloc(n * sizeof(int));
    if(items == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        items[i] = removeHeap(heap);
    }
    return items;
}

int main() {
    int size = 10;
    int prices[] = {5, 9, 3, 7, 2, 8, 6, 1, 4};
    Heap *heap = createHeap(size);
    for (int i = 0; i < size; ++i) {
        insertHeap(heap, prices[i]);
    }

    int n = 3;
    int *items = cheapItems(heap, n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", items[i]);
    }
    free(items);
    free(heap->data);
    free(heap);

    return 0;
}