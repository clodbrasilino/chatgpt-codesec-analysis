#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double price;
} Item;

typedef struct {
    Item *data;
    int size;
    int capacity;
} MinHeap;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap *create_min_heap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (heap == NULL) {
        return NULL;
    }
    heap->data = (Item *)malloc(sizeof(Item) * capacity);
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroy_min_heap(MinHeap *heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

void heapify_down(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left].price < heap->data[smallest].price) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right].price < heap->data[smallest].price) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void heapify_up(MinHeap *heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->data[index].price < heap->data[parent].price) {
        swap(&heap->data[index], &heap->data[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

int heap_insert(MinHeap *heap, Item item) {
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = item;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

Item heap_extract_min(MinHeap *heap) {
    Item min_item = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return min_item;
}

Item heap_peek_min(MinHeap *heap) {
    return heap->data[0];
}

Item *find_n_expensive_items(Item *items, int total_items, int n, int *result_count) {
    if (items == NULL || total_items <= 0 || n <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    if (n > total_items) {
        n = total_items;
    }

    MinHeap *heap = create_min_heap(n);
    if (heap == NULL) {
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < total_items; i++) {
        if (heap->size < n) {
            if (heap_insert(heap, items[i]) != 0) {
                destroy_min_heap(heap);
                *result_count = 0;
                return NULL;
            }
        } else if (items[i].price > heap_peek_min(heap).price) {
            heap_extract_min(heap);
            if (heap_insert(heap, items[i]) != 0) {
                destroy_min_heap(heap);
                *result_count = 0;
                return NULL;
            }
        }
    }

    Item *result = (Item *)malloc(sizeof(Item) * heap->size);
    if (result == NULL) {
        destroy_min_heap(heap);
        *result_count = 0;
        return NULL;
    }

    *result_count = heap->size;
    for (int i = heap->size - 1; i >= 0; i--) {
        result[i] = heap_extract_min(heap);
    }

    destroy_min_heap(heap);
    return result;
}

int main(void) {
    Item items[] = {
        {1, 10.5},
        {2, 20.0},
        {3, 5.25},
        {4, 15.75},
        {5, 30.0},
        {6, 25.5},
        {7, 8.0},
        {8, 12.25}
    };
    int total_items = sizeof(items) / sizeof(items[0]);
    int n = 3;
    int result_count = 0;

    Item *expensive_items = find_n_expensive_items(items, total_items, n, &result_count);

    if (expensive_items != NULL) {
        printf("Top %d expensive items:\n", result_count);
        for (int i = 0; i < result_count; i++) {
            printf("ID: %d, Price: %.2f\n", expensive_items[i].id, expensive_items[i].price);
        }
        free(expensive_items);
    } else {
        printf("Failed to find expensive items.\n");
    }

    return 0;
}