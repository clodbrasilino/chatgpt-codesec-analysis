#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int id;
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MaxHeap;

static void swap_items(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

static void max_heapify(MaxHeap *heap, size_t index) {
    size_t largest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->data[left].price > heap->data[largest].price) {
        largest = left;
    }

    if (right < heap->size && heap->data[right].price > heap->data[largest].price) {
        largest = right;
    }

    if (largest != index) {
        swap_items(&heap->data[index], &heap->data[largest]);
        max_heapify(heap, largest);
    }
}

static MaxHeap* create_max_heap(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }

    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    if (!heap) {
        return NULL;
    }

    heap->data = (Item *)malloc(capacity * sizeof(Item));
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void destroy_max_heap(MaxHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

static int insert_max_heap(MaxHeap *heap, Item item) {
    if (heap->size >= heap->capacity) {
        return -1;
    }

    size_t current = heap->size;
    heap->data[current] = item;
    heap->size++;

    while (current > 0) {
        size_t parent = (current - 1) / 2;
        if (heap->data[current].price > heap->data[parent].price) {
            swap_items(&heap->data[current], &heap->data[parent]);
            current = parent;
        } else {
            break;
        }
    }

    return 0;
}

Item* get_n_cheapest_items(const Item *dataset, size_t dataset_size, size_t n, size_t *out_count) {
    if (!dataset || dataset_size == 0 || n == 0 || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    size_t target_count = (n > dataset_size) ? dataset_size : n;
    MaxHeap *heap = create_max_heap(target_count);
    if (!heap) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < target_count; i++) {
        if (insert_max_heap(heap, dataset[i]) != 0) {
            destroy_max_heap(heap);
            *out_count = 0;
            return NULL;
        }
    }

    for (size_t i = target_count; i < dataset_size; i++) {
        if (dataset[i].price < heap->data[0].price) {
            heap->data[0] = dataset[i];
            max_heapify(heap, 0);
        }
    }

    Item *result = (Item *)malloc(target_count * sizeof(Item));
    if (!result) {
        destroy_max_heap(heap);
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < target_count; i++) {
        result[i] = heap->data[i];
    }
    
    *out_count = target_count;

    destroy_max_heap(heap);
    return result;
}

int main(void) {
    Item dataset[] = {
        {1, 45.99}, {2, 12.50}, {3, 99.99}, {4, 5.00},
        {5, 75.25}, {6, 19.99}, {7, 8.50},  {8, 150.00},
        {9, 3.25},  {10, 25.00}
    };
    
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;
    size_t found_count = 0;

    Item *cheapest_items = get_n_cheapest_items(dataset, dataset_size, n, &found_count);

    if (cheapest_items) {
        for (size_t i = 0; i < found_count; i++) {
            printf("ID: %u, Price: %.2f\n", cheapest_items[i].id, cheapest_items[i].price);
        }
        free(cheapest_items);
    } else {
        fprintf(stderr, "Error processing the dataset or out of memory.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}