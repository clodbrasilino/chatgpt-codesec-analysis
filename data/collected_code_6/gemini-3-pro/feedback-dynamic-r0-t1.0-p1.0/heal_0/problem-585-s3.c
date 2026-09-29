#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    double price;
} Item;

typedef struct {
    Item* items;
    size_t capacity;
    size_t size;
} MinHeap;

MinHeap* createMinHeap(size_t capacity) {
    if (capacity == 0) return NULL;
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->items = (Item*)malloc(capacity * sizeof(Item));
    if (!heap->items) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void freeMinHeap(MinHeap* heap) {
    if (heap) {
        free(heap->items);
        free(heap);
    }
}

void swapItems(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, size_t idx) {
    size_t smallest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if (left < heap->size && heap->items[left].price < heap->items[smallest].price)
        smallest = left;

    if (right < heap->size && heap->items[right].price < heap->items[smallest].price)
        smallest = right;

    if (smallest != idx) {
        swapItems(&heap->items[idx], &heap->items[smallest]);
        minHeapify(heap, smallest);
    }
}

int insertMinHeap(MinHeap* heap, Item item) {
    if (!heap) return -1;
    if (heap->size < heap->capacity) {
        size_t i = heap->size++;
        heap->items[i] = item;
        while (i != 0 && heap->items[(i - 1) / 2].price > heap->items[i].price) {
            swapItems(&heap->items[i], &heap->items[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (item.price > heap->items[0].price) {
        heap->items[0] = item;
        minHeapify(heap, 0);
    }
    return 0;
}

Item* findNMostExpensive(const Item* dataset, size_t dataSize, size_t n, size_t* outSize) {
    if (!dataset || dataSize == 0 || n == 0 || !outSize) return NULL;

    size_t heapCapacity = n > dataSize ? dataSize : n;
    MinHeap* heap = createMinHeap(heapCapacity);
    if (!heap) return NULL;

    for (size_t i = 0; i < dataSize; ++i) {
        if (insertMinHeap(heap, dataset[i]) != 0) {
            freeMinHeap(heap);
            return NULL;
        }
    }

    Item* result = (Item*)malloc(heap->size * sizeof(Item));
    if (!result) {
        freeMinHeap(heap);
        return NULL;
    }

    *outSize = heap->size;
    for (size_t i = 0; i < heap->size; ++i) {
        result[i] = heap->items[i];
    }

    for (size_t i = 0; i < heap->size - 1; ++i) {
        for (size_t j = 0; j < heap->size - i - 1; ++j) {
            if (result[j].price < result[j + 1].price) {
                swapItems(&result[j], &result[j + 1]);
            }
        }
    }

    freeMinHeap(heap);
    return result;
}

int main(void) {
    Item dataset[] = {
        {"Item A", 10.5},
        {"Item B", 50.0},
        {"Item C", 20.75},
        {"Item D", 100.0},
        {"Item E", 5.25},
        {"Item F", 75.5}
    };
    size_t dataSize = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    size_t resultSize = 0;

    Item* expensiveItems = findNMostExpensive(dataset, dataSize, n, &resultSize);
    
    if (expensiveItems) {
        for (size_t i = 0; i < resultSize; ++i) {
            printf("%s: $%.2f\n", expensiveItems[i].name, expensiveItems[i].price);
        }
        free(expensiveItems);
    } else {
        printf("Failed to find expensive items.\n");
    }

    return 0;
}