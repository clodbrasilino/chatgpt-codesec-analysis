#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double price;
} item_t;

typedef struct {
    item_t *items;
    size_t size;
    size_t capacity;
} max_heap_t;

max_heap_t* create_heap(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    
    max_heap_t *heap = (max_heap_t*)malloc(sizeof(max_heap_t));
    if (!heap) {
        return NULL;
    }
    
    heap->items = (item_t*)malloc(capacity * sizeof(item_t));
    if (!heap->items) {
        free(heap);
        return NULL;
    }
    
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void free_heap(max_heap_t *heap) {
    if (heap) {
        if (heap->items) {
            free(heap->items);
        }
        free(heap);
    }
}

void swap_items(item_t *a, item_t *b) {
    item_t temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(max_heap_t *heap, size_t index) {
    size_t largest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->items[left].price > heap->items[largest].price) {
        largest = left;
    }
    
    if (right < heap->size && heap->items[right].price > heap->items[largest].price) {
        largest = right;
    }
    
    if (largest != index) {
        swap_items(&heap->items[index], &heap->items[largest]);
        heapify_down(heap, largest);
    }
}

void heapify_up(max_heap_t *heap, size_t index) {
    if (index > 0 && heap->items[(index - 1) / 2].price < heap->items[index].price) {
        swap_items(&heap->items[(index - 1) / 2], &heap->items[index]);
        heapify_up(heap, (index - 1) / 2);
    }
}

int insert_heap(max_heap_t *heap, item_t item) {
    if (!heap) {
        return -1;
    }
    
    if (heap->size < heap->capacity) {
        heap->items[heap->size] = item;
        heapify_up(heap, heap->size);
        heap->size++;
    } else if (item.price < heap->items[0].price) {
        heap->items[0] = item;
        heapify_down(heap, 0);
    }
    
    return 0;
}

item_t* find_n_cheapest(const item_t *dataset, size_t data_size, size_t n, size_t *out_size) {
    if (!dataset || data_size == 0 || n == 0 || !out_size) {
        if (out_size) {
            *out_size = 0;
        }
        return NULL;
    }

    size_t actual_n = (n < data_size) ? n : data_size;
    max_heap_t *heap = create_heap(actual_n);
    if (!heap) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < data_size; i++) {
        if (insert_heap(heap, dataset[i]) != 0) {
            free_heap(heap);
            *out_size = 0;
            return NULL;
        }
    }

    item_t *result = (item_t*)malloc(actual_n * sizeof(item_t));
    if (!result) {
        free_heap(heap);
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < actual_n; i++) {
        result[i] = heap->items[i];
    }

    *out_size = actual_n;
    free_heap(heap);
    
    return result;
}

int main(void) {
    item_t dataset[] = {
        {1, 29.99},
        {2, 15.50},
        {3, 9.99},
        {4, 49.99},
        {5, 5.00},
        {6, 12.00},
        {7, 99.99},
        {8, 3.50},
        {9, 8.25},
        {10, 10.00}
    };
    
    size_t data_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t result_size = 0;

    item_t *cheapest_items = find_n_cheapest(dataset, data_size, n, &result_size);

    if (!cheapest_items) {
        fprintf(stderr, "Failed to process data or allocate memory.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_size; i++) {
        printf("ID: %d, Price: %.2f\n", cheapest_items[i].id, cheapest_items[i].price);
    }

    free(cheapest_items);
    return EXIT_SUCCESS;
}