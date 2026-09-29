#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct {
    int price;
    int index;
} Item;

typedef struct {
    Item data[MAXSIZE];
    int size;
} Heap;

Heap *createHeap() {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->size = 0;
    return heap;
}

void pushHeap(Heap *heap, int price, int index) {
    int i = heap->size++;
    while (i && heap->data[(i - 1) / 2].price < price) {
        heap->data[i] = heap->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->data[i].price = price;
    heap->data[i].index = index;
}

Item popHeap(Heap *heap) {
    int i, child;
    Item min, last;
    min = heap->data[0];
    last = heap->data[--heap->size];
    for (i = 0; i * 2 + 1 < heap->size; i = child) {
        child = i * 2 + 1;
        if (child < heap->size - 1 && heap->data[child].price < heap->data[child + 1].price) {
            child++;
        }
        if (last.price < heap->data[child].price) {
            heap->data[i] = heap->data[child];
        } else {
            break;
        }
    }
    heap->data[i] = last;
    return min;
}

int *findTopNPrices(int *prices, int size, int n) {
    int i;
    Heap *heap = createHeap();
    for (i = 0; i < size; i++) {
        pushHeap(heap, prices[i], i);
        if (heap->size > n) {
            popHeap(heap);
        }
    }
    int *topPrices = (int *) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        topPrices[i] = popHeap(heap).price;
    }
    free(heap);
    return topPrices;
}

int main() {
    int data[] = {1, 20, 6, 4, 5, 19, 100, 23, 45, 67, 89};
    int n = 5;
    int *topPrices = findTopNPrices(data, sizeof(data) / sizeof(data[0]), n);
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", topPrices[i]);
    }
    free(topPrices);
    return 0;
}