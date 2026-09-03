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
    if (index > 0 && heap->data[index].price < heap->data[parent].price) {
        swap(&heap->data[index], &heap->data[parent]);
        heapify_up(heap, parent);
    }
}

int heap_insert(MinHeap *heap, Item item) {
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = item;
    heap->size++;
    heapify_up(heap, heap->size - 1);
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

int compare_items_desc(const void *a, const void *b) {
    const Item *item_a = (const Item *)a;
    const Item *item_b = (const Item *)b;
    if (item_b->price > item_a->price) return 1;
    if (item_b->price < item_a->price) return -1;
    return 0;
}

Item *find_n_expensive_items(Item *dataset, int dataset_size, int n, int *result_size) {
    if (dataset == NULL || dataset_size <= 0 || n <= 0 || result_size == NULL) {
        *result_size = 0;
        return NULL;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    MinHeap *heap = create_min_heap(n);
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < dataset_size; i++) {
        if (heap->size < n) {
            if (heap_insert(heap, dataset[i]) != 0) {
                destroy_min_heap(heap);
                *result_size = 0;
                return NULL;
            }
        } else if (dataset[i].price > heap_peek_min(heap).price) {
            heap_extract_min(heap);
            if (heap_insert(heap, dataset[i]) != 0) {
                destroy_min_heap(heap);
                *result_size = 0;
                return NULL;
            }
        }
    }

    Item *result = (Item *)malloc(sizeof(Item) * heap->size);
    if (result == NULL) {
        destroy_min_heap(heap);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < heap->size; i++) {
        result[i] = heap->data[i];
    }

    qsort(result, heap->size, sizeof(Item), compare_items_desc);

    *result_size = heap->size;
    destroy_min_heap(heap);
    return result;
}

int main(void) {
    Item dataset[] = {
        {1, 10.5},
        {2, 20.0},
        {3, 5.25},
        {4, 15.75},
        {5, 30.0},
        {6, 25.5},
        {7, 8.0},
        {8, 12.0}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;

    Item *result = find_n_expensive_items(dataset, dataset_size, n, &result_size);

    if (result != NULL) {
        printf("Top %d expensive items:\n", result_size);
        for (int i = 0; i < result_size; i++) {
            printf("ID: %d, Price: %.2f\n", result[i].id, result[i].price);
        }
        free(result);
    } else {
        printf("Failed to find expensive items.\n");
    }

    return 0;
}