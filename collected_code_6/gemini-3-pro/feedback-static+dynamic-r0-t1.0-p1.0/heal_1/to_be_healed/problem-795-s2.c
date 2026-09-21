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

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(Item *heap, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].price > heap[largest].price) {
        largest = left;
    }
    if (right < n && heap[right].price > heap[largest].price) {
        largest = right;
    }
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        max_heapify(heap, n, largest);
    }
}

void build_max_heap(Item *heap, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(heap, n, i);
    }
}

Item* find_n_cheapest_items(const Item *dataset, int dataset_size, int n) {
    if (dataset == NULL || dataset_size <= 0 || n <= 0) {
        return NULL;
    }
    if (n > dataset_size) {
        n = dataset_size;
    }

    Item *heap = (Item *)malloc(n * sizeof(Item));
    if (heap == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        heap[i] = dataset[i];
    }

    build_max_heap(heap, n);

    for (int i = n; i < dataset_size; i++) {
        if (dataset[i].price < heap[0].price) {
            heap[0] = dataset[i];
            max_heapify(heap, n, 0);
        }
    }

    return heap;
}

int main(void) {
    Item dataset[] = {
        {"Item A", 50.0},
        {"Item B", 10.0},
        {"Item C", 30.0},
        {"Item D", 20.0},
        {"Item E", 40.0},
        {"Item F", 5.0},
        {"Item G", 15.0}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;

    Item *cheapest_items = find_n_cheapest_items(dataset, dataset_size, n);
    if (cheapest_items == NULL) {
        fprintf(stderr, "Error allocating memory or invalid input.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        printf("%s: %.2f\n", cheapest_items[i].name, cheapest_items[i].price);
    }

    free(cheapest_items);
    return EXIT_SUCCESS;
}