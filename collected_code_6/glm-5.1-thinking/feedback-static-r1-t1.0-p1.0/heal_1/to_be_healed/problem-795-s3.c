#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int price;
    int id;
} Item;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(Item *heap, size_t size, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < size && heap[left].price > heap[largest].price) {
        largest = left;
    }

    if (right < size && heap[right].price > heap[largest].price) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        max_heapify(heap, size, largest);
    }
}

void insert_max_heap(Item *heap, size_t *size, size_t capacity, Item item) {
    if (*size < capacity) {
        heap[*size] = item;
        size_t i = *size;
        (*size)++;
        while (i != 0 && heap[(i - 1) / 2].price < heap[i].price) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else {
        if (item.price < heap[0].price) {
            heap[0] = item;
            max_heapify(heap, *size, 0);
        }
    }
}

void heap_sort_ascending(Item *heap, size_t size) {
    for (size_t i = size - 1; i > 0; i--) {
        swap(&heap[0], &heap[i]);
        max_heapify(heap, i, 0);
    }
}

/* Possible weaknesses found:
 *  Parameter 'dataset' can be declared as pointer to const [constParameterPointer]
 */
Item* find_n_cheapest(Item *dataset, size_t dataset_size, size_t n, size_t *result_size) {
    if (dataset == NULL || result_size == NULL || n == 0 || dataset_size == 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    size_t heap_capacity = n;
    if (dataset_size < n) {
        heap_capacity = dataset_size;
    }

    if (heap_capacity > SIZE_MAX / sizeof(Item)) {
        *result_size = 0;
        return NULL;
    }

    Item *heap = (Item *)malloc(heap_capacity * sizeof(Item));
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t heap_size = 0;
    for (size_t i = 0; i < dataset_size; i++) {
        insert_max_heap(heap, &heap_size, heap_capacity, dataset[i]);
    }

    heap_sort_ascending(heap, heap_size);

    *result_size = heap_size;
    return heap;
}

int main(void) {
    Item dataset[] = {
        {100, 1}, {50, 2}, {20, 3}, {80, 4}, {10, 5}, {60, 6}, {30, 7}
    };
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t result_size = 0;

    Item *cheapest_items = find_n_cheapest(dataset, dataset_size, n, &result_size);

    if (cheapest_items != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("Item ID: %d, Price: %d\n", cheapest_items[i].id, cheapest_items[i].price);
        }
        free(cheapest_items);
    } else {
        printf("No items found or memory allocation failed.\n");
    }

    return 0;
}