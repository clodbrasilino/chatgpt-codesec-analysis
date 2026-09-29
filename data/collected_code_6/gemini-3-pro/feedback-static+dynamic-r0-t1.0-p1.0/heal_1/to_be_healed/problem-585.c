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
    Item* array;
    int capacity;
    int size;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) {
        return NULL;
    }
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (Item*)malloc(minHeap->capacity * sizeof(Item));
    if (!minHeap->array) {
        free(minHeap);
        return NULL;
    }
    return minHeap;
}

void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].price < minHeap->array[smallest].price) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right].price < minHeap->array[smallest].price) {
        smallest = right;
    }

    if (smallest != idx) {
        swap(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

void insertHelper(MinHeap* minHeap, Item item) {
    if (minHeap->size == minHeap->capacity) {
        if (item.price > minHeap->array[0].price) {
            minHeap->array[0] = item;
            minHeapify(minHeap, 0);
        }
    } else {
        int i = minHeap->size;
        minHeap->size++;
        minHeap->array[i] = item;

        while (i != 0 && minHeap->array[(i - 1) / 2].price > minHeap->array[i].price) {
            swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'dataset' can be declared as pointer to const [constParameterPointer]
 */
Item* findNMostExpensive(Item* dataset, int dataSize, int n, int* resultSize) {
    if (!dataset || dataSize <= 0 || n <= 0 || !resultSize) {
        if (resultSize) *resultSize = 0;
        return NULL;
    }

    int heapSize = (n < dataSize) ? n : dataSize;
    MinHeap* minHeap = createMinHeap(heapSize);
    if (!minHeap) {
        *resultSize = 0;
        return NULL;
    }

    for (int i = 0; i < dataSize; i++) {
        insertHelper(minHeap, dataset[i]);
    }

    Item* result = (Item*)malloc(minHeap->size * sizeof(Item));
    if (!result) {
        free(minHeap->array);
        free(minHeap);
        *resultSize = 0;
        return NULL;
    }

    for (int i = 0; i < minHeap->size; i++) {
        result[i] = minHeap->array[i];
    }
    *resultSize = minHeap->size;

    free(minHeap->array);
    free(minHeap);

    return result;
}

int main(void) {
    Item dataset[] = {
        {"Item A", 10.5},
        {"Item B", 50.0},
        {"Item C", 5.0},
        {"Item D", 100.0},
        {"Item E", 75.5},
        {"Item F", 30.0}
    };
    int dataSize = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int resultSize = 0;

    Item* topItems = findNMostExpensive(dataset, dataSize, n, &resultSize);

    if (topItems) {
        for (int i = 0; i < resultSize; i++) {
            printf("%s: $%.2f\n", topItems[i].name, topItems[i].price);
        }
        free(topItems);
    }

    return 0;
}