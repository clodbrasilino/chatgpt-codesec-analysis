#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double price;
} Item;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(Item *heap, int heap_size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && heap[left].price > heap[largest].price) {
        largest = left;
    }

    if (right < heap_size && heap[right].price > heap[largest].price) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        max_heapify(heap, heap_size, largest);
    }
}

Item* find_n_cheapest(Item *dataset, int dataset_size, int n, int *result_size) {
    if (n <= 0) {
        *result_size = 0;
        return NULL;
    }

    int actual_n = n;
    if (dataset_size < n) {
        actual_n = dataset_size;
    }

    Item *heap = (Item *)malloc(actual_n * sizeof(Item));
    if (!heap) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < actual_n; i++) {
        heap[i] = dataset[i];
    }

    for (int i = (actual_n / 2) - 1; i >= 0; i--) {
        max_heapify(heap, actual_n, i);
    }

    for (int i = actual_n; i < dataset_size; i++) {
        if (dataset[i].price < heap[0].price) {
            heap[0] = dataset[i];
            max_heapify(heap, actual_n, 0);
        }
    }

    *result_size = actual_n;
    return heap;
}

int main() {
    Item dataset[] = {
        {1, 10.5},
        {2, 5.2},
        {3, 20.0},
        {4, 8.9},
        {5, 1.5},
        {6, 15.0},
        {7, 3.3}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;

    Item *cheapest = find_n_cheapest(dataset, dataset_size, n, &result_size);

    if (cheapest) {
        for (int i = 0; i < result_size; i++) {
            printf("Item ID: %d, Price: %.2f\n", cheapest[i].id, cheapest[i].price);
        }
        free(cheapest);
    }

    return 0;
}