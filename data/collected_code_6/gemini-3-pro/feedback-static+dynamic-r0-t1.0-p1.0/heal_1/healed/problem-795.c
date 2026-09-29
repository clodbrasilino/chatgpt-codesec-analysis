#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    double price;
} Item;

void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Item arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].price > arr[largest].price) {
        largest = left;
    }

    if (right < n && arr[right].price > arr[largest].price) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(Item arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

Item* findNCheapest(Item dataset[], int dataSize, int n) {
    if (n <= 0 || dataSize <= 0) {
        return NULL;
    }

    if (n > dataSize) {
        n = dataSize;
    }

    Item* heap = (Item*)malloc(n * sizeof(Item));
    if (!heap) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        heap[i] = dataset[i];
    }

    buildMaxHeap(heap, n);

    for (int i = n; i < dataSize; i++) {
        if (dataset[i].price < heap[0].price) {
            heap[0] = dataset[i];
            maxHeapify(heap, n, 0);
        }
    }

    return heap;
}

int main(void) {
    Item dataset[] = {
        {"Laptop", 999.99},
        {"Mouse", 25.50},
        {"Keyboard", 45.00},
        {"Monitor", 200.00},
        {"USB Drive", 15.99},
        {"Headphones", 85.00},
        {"Webcam", 60.00}
    };
    int dataSize = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;

    Item* cheapestItems = findNCheapest(dataset, dataSize, n);

    if (cheapestItems) {
        for (int i = 0; i < n && i < dataSize; i++) {
            printf("%s: $%.2f\n", cheapestItems[i].name, cheapestItems[i].price);
        }
        free(cheapestItems);
    }

    return 0;
}