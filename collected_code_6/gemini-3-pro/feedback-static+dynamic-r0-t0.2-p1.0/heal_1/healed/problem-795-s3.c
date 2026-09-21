#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
    double price;
} Item;

typedef struct {
    Item* array;
    int capacity;
    int size;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity) {
    if (capacity <= 0) return NULL;
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (!heap) return NULL;
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (Item*)malloc(capacity * sizeof(Item));
    if (!heap->array) {
        free(heap);
        return NULL;
    }
    return heap;
}

void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MaxHeap* heap, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].price > heap->array[largest].price)
        largest = left;

    if (right < heap->size && heap->array[right].price > heap->array[largest].price)
        largest = right;

    if (largest != idx) {
        swap(&heap->array[idx], &heap->array[largest]);
        maxHeapify(heap, largest);
    }
}

void insertMaxHeap(MaxHeap* heap, Item item) {
    if (!heap) return;
    if (heap->size < heap->capacity) {
        heap->array[heap->size] = item;
        int i = heap->size;
        heap->size++;
        while (i != 0 && heap->array[(i - 1) / 2].price < heap->array[i].price) {
            swap(&heap->array[i], &heap->array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (item.price < heap->array[0].price) {
        heap->array[0] = item;
        maxHeapify(heap, 0);
    }
}

void freeMaxHeap(MaxHeap* heap) {
    if (heap) {
        if (heap->array) {
            free(heap->array);
        }
        free(heap);
    }
}

Item* findNCheapestItems(const Item* dataset, int datasetSize, int n, int* resultSize) {
    if (!dataset || datasetSize <= 0 || n <= 0 || !resultSize) {
        if (resultSize) *resultSize = 0;
        return NULL;
    }

    int heapCapacity = (n < datasetSize) ? n : datasetSize;
    MaxHeap* heap = createMaxHeap(heapCapacity);
    if (!heap) {
        *resultSize = 0;
        return NULL;
    }

    for (int i = 0; i < datasetSize; i++) {
        insertMaxHeap(heap, dataset[i]);
    }

    Item* result = (Item*)malloc(heap->size * sizeof(Item));
    if (!result) {
        freeMaxHeap(heap);
        *resultSize = 0;
        return NULL;
    }

    *resultSize = heap->size;
    for (int i = 0; i < heap->size; i++) {
        result[i] = heap->array[i];
    }

    freeMaxHeap(heap);
    return result;
}

int main(void) {
    Item dataset[] = {
        {"Item A", 45.99},
        {"Item B", 12.50},
        {"Item C", 9.99},
        {"Item D", 105.00},
        {"Item E", 3.50},
        {"Item F", 24.00},
        {"Item G", 8.75}
    };
    int datasetSize = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int resultSize = 0;

    Item* cheapestItems = findNCheapestItems(dataset, datasetSize, n, &resultSize);

    if (cheapestItems) {
        for (int i = 0; i < resultSize; i++) {
            printf("%s: $%.2f\n", cheapestItems[i].name, cheapestItems[i].price);
        }
        free(cheapestItems);
    }

    return 0;
}