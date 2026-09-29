#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[64];
    double price;
} Item;

typedef struct {
    Item *data;
    int size;
    int capacity;
} MaxHeap;

static void swap_items(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

static void max_heapify_down(MaxHeap *heap, int index) {
    while (1) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap->size && heap->data[left].price > heap->data[largest].price) {
            largest = left;
        }
        if (right < heap->size && heap->data[right].price > heap->data[largest].price) {
            largest = right;
        }
        if (largest == index) {
            break;
        }

        swap_items(&heap->data[index], &heap->data[largest]);
        index = largest;
    }
}

static void max_heapify_up(MaxHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index].price > heap->data[parent].price) {
            swap_items(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

static void max_heap_push(MaxHeap *heap, Item item) {
    heap->data[heap->size] = item;
    max_heapify_up(heap, heap->size);
    heap->size++;
}

static Item max_heap_pop(MaxHeap *heap) {
    Item top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    max_heapify_down(heap, 0);
    return top;
}

static Item max_heap_peek(const MaxHeap *heap) {
    return heap->data[0];
}

Item *find_n_cheapest_items(const Item *dataset, int dataset_size, int n, int *result_size) {
    if (dataset == NULL || dataset_size <= 0 || n <= 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    MaxHeap heap;
    heap.data = malloc((size_t)n * sizeof(Item));
    if (heap.data == NULL) {
        *result_size = 0;
        return NULL;
    }

    heap.size = 0;
    heap.capacity = n;

    for (int i = 0; i < dataset_size; i++) {
        if (heap.size < n) {
            max_heap_push(&heap, dataset[i]);
        } else if (dataset[i].price < max_heap_peek(&heap).price) {
            max_heap_pop(&heap);
            max_heap_push(&heap, dataset[i]);
        }
    }

    *result_size = heap.size;

    Item *result = malloc((size_t)heap.size * sizeof(Item));
    if (result == NULL) {
        free(heap.data);
        *result_size = 0;
        return NULL;
    }

    memcpy(result, heap.data, (size_t)heap.size * sizeof(Item));
    free(heap.data);

    return result;
}

static int compare_items_by_price(const void *a, const void *b) {
    const Item *item_a = (const Item *)a;
    const Item *item_b = (const Item *)b;

    if (item_a->price < item_b->price) {
        return -1;
    }
    if (item_a->price > item_b->price) {
        return 1;
    }
    return 0;
}

int main(void) {
    Item dataset[] = {
        {"apple", 1.20},
        {"banana", 0.80},
        {"cherry", 3.50},
        {"date", 2.10},
        {"elderberry", 1.50},
        {"fig", 0.90}
    };

    int dataset_size = (int)(sizeof(dataset) / sizeof(dataset[0]));
    int n = 3;
    int result_size = 0;

    Item *cheapest = find_n_cheapest_items(dataset, dataset_size, n, &result_size);

    if (cheapest == NULL) {
        fprintf(stderr, "Failed to find cheapest items\n");
        return EXIT_FAILURE;
    }

    qsort(cheapest, (size_t)result_size, sizeof(Item), compare_items_by_price);

    printf("Cheapest %d items:\n", result_size);
    for (int i = 0; i < result_size; i++) {
        printf("%s: %.2f\n", cheapest[i].name, cheapest[i].price);
    }

    free(cheapest);

    return EXIT_SUCCESS;
}