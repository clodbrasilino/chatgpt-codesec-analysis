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
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    if (capacity <= 0) return NULL;
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) return NULL;
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (Item*)malloc(capacity * sizeof(Item));
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
    if (!minHeap) return;
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].price < minHeap->array[smallest].price)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].price < minHeap->array[smallest].price)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[idx], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

void insertHelper(MinHeap* minHeap, Item item) {
    if (!minHeap || minHeap->size == 0) return;
    if (item.price > minHeap->array[0].price) {
        minHeap->array[0] = item;
        minHeapify(minHeap, 0);
    }
}

void buildInitialHeap(MinHeap* minHeap, const Item* item) {
    if (!minHeap || !item) return;
    minHeap->array[minHeap->size] = *item;
    int curr = minHeap->size;
    minHeap->size++;
    while (curr != 0 && minHeap->array[(curr - 1) / 2].price > minHeap->array[curr].price) {
        swap(&minHeap->array[curr], &minHeap->array[(curr - 1) / 2]);
        curr = (curr - 1) / 2;
    }
}

void findNExpensiveItems(Item* dataset, int datasetSize, int n) {
    if (!dataset || datasetSize <= 0 || n <= 0) return;
    
    if (n > datasetSize) n = datasetSize;

    MinHeap* minHeap = createMinHeap(n);
    if (!minHeap) return;

    for (int i = 0; i < n; i++) {
        buildInitialHeap(minHeap, &dataset[i]);
    }

    for (int i = n; i < datasetSize; i++) {
        insertHelper(minHeap, dataset[i]);
    }

    Item* result = (Item*)malloc(n * sizeof(Item));
    if (!result) {
        free(minHeap->array);
        free(minHeap);
        return;
    }

    for (int i = n - 1; i >= 0; i--) {
        result[i] = minHeap->array[0];
        minHeap->array[0] = minHeap->array[minHeap->size - 1];
        minHeap->size--;
        minHeapify(minHeap, 0);
    }

    for (int i = 0; i < n; i++) {
        printf("%s: $%.2f\n", result[i].name, result[i].price);
    }

    free(result);
    free(minHeap->array);
    free(minHeap);
}

int main(void) {
    Item dataset[] = {
        {"Laptop", 1200.50},
        {"Mouse", 25.99},
        {"Keyboard", 75.00},
        {"Monitor", 300.00},
        {"Smartphone", 800.00},
        {"Tablet", 450.00},
        {"Headphones", 150.00},
        {"Chair", 200.00}
    };
    int datasetSize = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;

    findNExpensiveItems(dataset, datasetSize, n);

    return 0;
}