#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MinHeap;

void swap_items(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(MinHeap *heap, size_t index) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->data[left].price < heap->data[smallest].price) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right].price < heap->data[smallest].price) {
        smallest = right;
    }
    if (smallest != index) {
        swap_items(&heap->data[index], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void heapify_up(MinHeap *heap, size_t index) {
    if (index > 0 && heap->data[(index - 1) / 2].price > heap->data[index].price) {
        swap_items(&heap->data[index], &heap->data[(index - 1) / 2]);
        heapify_up(heap, (index - 1) / 2);
    }
}

int insert_heap(MinHeap *heap, Item item) {
    if (heap->size == heap->capacity) {
        if (item.price > heap->data[0].price) {
            heap->data[0] = item;
            heapify_down(heap, 0);
        }
        return 0;
    }
    heap->data[heap->size] = item;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

Item* find_n_expensive_items(const Item *dataset, size_t dataset_size, size_t n, size_t *out_count) {
    size_t capacity;
    MinHeap heap;

    if (!dataset || dataset_size == 0 || n == 0 || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    capacity = (n < dataset_size) ? n : dataset_size;
    heap.size = 0;
    heap.capacity = capacity;
    heap.data = (Item *)malloc(capacity * sizeof(Item));

    if (!heap.data) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < dataset_size; i++) {
        insert_heap(&heap, dataset[i]);
    }

    *out_count = heap.size;
    return heap.data;
}

int main(void) {
    Item dataset[] = {
        {1, 15.50},
        {2, 8.99},
        {3, 120.00},
        {4, 45.75},
        {5, 2.50},
        {6, 99.99},
        {7, 300.00},
        {8, 55.00}
    };
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    size_t out_count = 0;

    Item *expensive_items = find_n_expensive_items(dataset, dataset_size, n, &out_count);

    if (!expensive_items) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < out_count; i++) {
        printf("Item ID: %d, Price: %.2f\n", expensive_items[i].id, expensive_items[i].price);
    }

    free(expensive_items);
    return EXIT_SUCCESS;
}