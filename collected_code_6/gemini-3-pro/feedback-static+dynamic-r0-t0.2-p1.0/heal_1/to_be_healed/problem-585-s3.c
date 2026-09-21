#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    double price;
} Item;

typedef struct {
    Item *items;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    if (capacity <= 0) return NULL;
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->items = (Item*)malloc(capacity * sizeof(Item));
    if (!heap->items) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->items[left].price < heap->items[smallest].price)
        smallest = left;

    if (right < heap->size && heap->items[right].price < heap->items[smallest].price)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->items[idx], &heap->items[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap *heap, Item item) {
    if (!heap) return;
    if (heap->size < heap->capacity) {
        heap->items[heap->size] = item;
        int i = heap->size;
        heap->size++;
        while (i != 0 && heap->items[(i - 1) / 2].price > heap->items[i].price) {
            swap(&heap->items[i], &heap->items[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (item.price > heap->items[0].price) {
        heap->items[0] = item;
        minHeapify(heap, 0);
    }
}

void freeMinHeap(MinHeap *heap) {
    if (heap) {
        if (heap->items) {
            free(heap->items);
        }
        free(heap);
    }
}

/* Possible weaknesses found:
 *  Parameter 'dataset' can be declared as pointer to const [constParameterPointer]
 */
Item* findNExpensiveItems(Item *dataset, int datasetSize, int n, int *resultSize) {
    if (!dataset || datasetSize <= 0 || n <= 0 || !resultSize) {
        if (resultSize) *resultSize = 0;
        return NULL;
    }

    int heapCapacity = (n < datasetSize) ? n : datasetSize;
    MinHeap *heap = createMinHeap(heapCapacity);
    if (!heap) {
        *resultSize = 0;
        return NULL;
    }

    for (int i = 0; i < datasetSize; i++) {
        insertMinHeap(heap, dataset[i]);
    }

    Item *result = (Item*)malloc(heap->size * sizeof(Item));
    if (!result) {
        freeMinHeap(heap);
        *resultSize = 0;
        return NULL;
    }

    *resultSize = heap->size;
    for (int i = 0; i < *resultSize; i++) {
        result[i] = heap->items[i];
    }

    freeMinHeap(heap);
    return result;
}

int main(void) {
    Item dataset[] = {
        {"ItemA", 10.5},
        {"ItemB", 50.0},
        {"ItemC", 5.0},
        {"ItemD", 100.0},
        {"ItemE", 75.5},
        {"ItemF", 20.0}
    };
    int datasetSize = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int resultSize = 0;

    Item *expensiveItems = findNExpensiveItems(dataset, datasetSize, n, &resultSize);

    if (expensiveItems) {
        for (int i = 0; i < resultSize; i++) {
            printf("%s: %.2f\n", expensiveItems[i].name, expensiveItems[i].price);
        }
        free(expensiveItems);
    }

    return 0;
}