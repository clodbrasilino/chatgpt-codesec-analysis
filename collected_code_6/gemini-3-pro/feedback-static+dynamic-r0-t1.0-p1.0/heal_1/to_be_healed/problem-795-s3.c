#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
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
    if (!heap) {
        return NULL;
    }
    heap->array = (Item*)malloc((size_t)capacity * sizeof(Item));
    if (!heap->array) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
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

    if (left < heap->size && heap->array[left].price > heap->array[largest].price) {
        largest = left;
    }
    if (right < heap->size && heap->array[right].price > heap->array[largest].price) {
        largest = right;
    }
    if (largest != idx) {
        swap(&heap->array[idx], &heap->array[largest]);
        maxHeapify(heap, largest);
    }
}

void insertMaxHeap(MaxHeap* heap, Item item) {
    if (heap->size < heap->capacity) {
        int i = heap->size;
        heap->array[i] = item;
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
            heap->array = NULL;
        }
        free(heap);
    }
}

/* Possible weaknesses found:
 *  Parameter 'dataset' can be declared as pointer to const [constParameterPointer]
 */
Item* findNCheapestItems(Item* dataset, int dataSize, int n, int* resultSize) {
    if (!dataset || dataSize <= 0 || n <= 0 || !resultSize) {
        if (resultSize) *resultSize = 0;
        return NULL;
    }

    int heapCapacity = (n < dataSize) ? n : dataSize;
    MaxHeap* heap = createMaxHeap(heapCapacity);
    if (!heap) {
        *resultSize = 0;
        return NULL;
    }

    for (int i = 0; i < dataSize; i++) {
        insertMaxHeap(heap, dataset[i]);
    }

    Item* result = (Item*)malloc((size_t)heap->size * sizeof(Item));
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
        {"ItemA", 45.0},
        {"ItemB", 12.5},
        {"ItemC", 89.9},
        {"ItemD", 5.0},
        {"ItemE", 23.4},
        {"ItemF", 15.0}
    };
    int dataSize = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int resultSize = 0;

    Item* cheapestItems = findNCheapestItems(dataset, dataSize, n, &resultSize);

    if (cheapestItems) {
        for (int i = 0; i < resultSize; i++) {
            printf("%s: %.2f\n", cheapestItems[i].name, cheapestItems[i].price);
        }
        free(cheapestItems);
        cheapestItems = NULL;
    } else {
        printf("Failed to find items or invalid input.\n");
    }

    return 0;
}