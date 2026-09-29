#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    double price;
} Item;

typedef struct {
    Item *items;
    size_t size;
    size_t capacity;
} MaxHeap;

static void heapify_up(MaxHeap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->items[index].price > heap->items[parent].price) {
            Item temp = heap->items[index];
            heap->items[index] = heap->items[parent];
            heap->items[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}

static void heapify_down(MaxHeap *heap, size_t index) {
    /* Possible weaknesses found:
     *  The scope of the variable 'largest' can be reduced. [variableScope]
     */
    size_t largest;
    /* Possible weaknesses found:
     *  The scope of the variable 'left' can be reduced. [variableScope]
     */
    size_t left;
    /* Possible weaknesses found:
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    size_t right;

    while (1) {
        largest = index;
        left = 2 * index + 1;
        right = 2 * index + 2;

        if (left < heap->size && heap->items[left].price > heap->items[largest].price) {
            largest = left;
        }
        if (right < heap->size && heap->items[right].price > heap->items[largest].price) {
            largest = right;
        }

        if (largest != index) {
            Item temp = heap->items[index];
            heap->items[index] = heap->items[largest];
            heap->items[largest] = temp;
            index = largest;
        } else {
            break;
        }
    }
}

static MaxHeap* create_heap(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }

    MaxHeap *heap = malloc(sizeof(MaxHeap));
    if (!heap) {
        return NULL;
    }

    heap->items = malloc(capacity * sizeof(Item));
    if (!heap->items) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void destroy_heap(MaxHeap *heap) {
    if (heap) {
        free(heap->items);
        free(heap);
    }
}

int find_n_cheapest(const Item *dataset, size_t data_size, size_t n, Item **result, size_t *result_size) {
    if (!dataset || !result || !result_size) {
        return -1;
    }

    if (n == 0 || data_size == 0) {
        *result = NULL;
        *result_size = 0;
        return 0;
    }

    size_t capacity = (n < data_size) ? n : data_size;
    MaxHeap *heap = create_heap(capacity);
    if (!heap) {
        return -1;
    }

    for (size_t i = 0; i < data_size; i++) {
        if (heap->size < heap->capacity) {
            heap->items[heap->size] = dataset[i];
            heapify_up(heap, heap->size);
            heap->size++;
        } else if (dataset[i].price < heap->items[0].price) {
            heap->items[0] = dataset[i];
            heapify_down(heap, 0);
        }
    }

    size_t out_size = heap->size;
    *result = malloc(out_size * sizeof(Item));
    if (!*result) {
        destroy_heap(heap);
        return -1;
    }

    for (size_t i = out_size; i > 0; i--) {
        (*result)[i - 1] = heap->items[0];
        heap->items[0] = heap->items[heap->size - 1];
        heap->size--;
        heapify_down(heap, 0);
    }

    *result_size = out_size;
    destroy_heap(heap);
    return 0;
}

int main(void) {
    Item dataset[] = {
        {"Laptop", 999.99},
        {"Mouse", 25.50},
        {"Keyboard", 45.00},
        {"Monitor", 150.75},
        {"Desk", 200.00},
        {"Chair", 85.25},
        {"Headphones", 60.00}
    };
    
    size_t data_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    Item *cheapest = NULL;
    size_t result_size = 0;

    int status = find_n_cheapest(dataset, data_size, n, &cheapest, &result_size);
    if (status != 0) {
        fprintf(stderr, "Error processing the dataset.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result_size; i++) {
        printf("%s: $%.2f\n", cheapest[i].name, cheapest[i].price);
    }

    free(cheapest);
    return EXIT_SUCCESS;
}