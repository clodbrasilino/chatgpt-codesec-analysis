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

void min_heapify(Item *heap, int heap_size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && heap[left].price < heap[smallest].price) {
        smallest = left;
    }

    if (right < heap_size && heap[right].price < heap[smallest].price) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        min_heapify(heap, heap_size, smallest);
    }
}

void build_min_heap(Item *heap, int heap_size) {
    for (int i = (heap_size / 2) - 1; i >= 0; i--) {
        min_heapify(heap, heap_size, i);
    }
}

Item* find_n_expensive(Item *dataset, int dataset_size, int n, int *result_size) {
    if (dataset == NULL || dataset_size <= 0 || n <= 0) {
        *result_size = 0;
        return NULL;
    }

    int actual_n = n;
    if (n > dataset_size) {
        actual_n = dataset_size;
    }

    Item *heap = (Item *)malloc(actual_n * sizeof(Item));
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < actual_n; i++) {
        heap[i] = dataset[i];
    }

    build_min_heap(heap, actual_n);

    for (int i = actual_n; i < dataset_size; i++) {
        if (dataset[i].price > heap[0].price) {
            heap[0] = dataset[i];
            min_heapify(heap, actual_n, 0);
        }
    }

    for (int i = actual_n - 1; i > 0; i--) {
        swap(&heap[0], &heap[i]);
        min_heapify(heap, i, 0);
    }

    *result_size = actual_n;
    return heap;
}

int main() {
    Item dataset[] = {
        {1, 10.5},
        {2, 25.0},
        {3, 15.75},
        {4, 50.0},
        {5, 5.25},
        {6, 35.1},
        {7, 20.0}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;

    Item *result = find_n_expensive(dataset, dataset_size, n, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("ID: %d, Price: %.2f\n", result[i].id, result[i].price);
        }
        free(result);
    } else {
        printf("No results found or invalid input.\n");
    }

    return 0;
}