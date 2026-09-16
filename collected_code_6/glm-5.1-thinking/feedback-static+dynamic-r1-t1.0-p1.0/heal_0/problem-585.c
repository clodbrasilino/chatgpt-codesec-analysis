#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int price;
} Item;

typedef struct {
    Item *data;
    int capacity;
    int size;
} MinHeap;

MinHeap* create_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (Item*)malloc(sizeof(Item) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index].price >= heap->data[parent].price) break;
        swap(&heap->data[index], &heap->data[parent]);
        index = parent;
    }
}

void heapify_down(MinHeap *heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < heap->size && heap->data[left].price < heap->data[smallest].price) smallest = left;
        if (right < heap->size && heap->data[right].price < heap->data[smallest].price) smallest = right;
        if (smallest == index) break;
        swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

void push(MinHeap *heap, Item item) {
    if (!heap || heap->size >= heap->capacity) return;
    heap->data[heap->size] = item;
    heapify_up(heap, heap->size);
    heap->size++;
}

Item top(MinHeap *heap) {
    Item empty = {0, 0};
    if (!heap || heap->size <= 0) return empty;
    return heap->data[0];
}

Item pop(MinHeap *heap) {
    Item empty = {0, 0};
    if (!heap || heap->size <= 0) return empty;
    Item item = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        heapify_down(heap, 0);
    }
    return item;
}

void free_heap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

Item* find_n_expensive(Item *dataset, int dataset_size, int n, int *result_size) {
    if (!dataset || dataset_size <= 0 || n <= 0 || !result_size) {
        if (result_size) *result_size = 0;
        return NULL;
    }
    int k = n > dataset_size ? dataset_size : n;
    MinHeap *heap = create_heap(k);
    if (!heap) {
        *result_size = 0;
        return NULL;
    }
    for (int i = 0; i < dataset_size; i++) {
        if (heap->size < k) {
            push(heap, dataset[i]);
        } else if (dataset[i].price > top(heap).price) {
            pop(heap);
            push(heap, dataset[i]);
        }
    }
    Item *result = (Item*)malloc(sizeof(Item) * heap->size);
    if (!result) {
        free_heap(heap);
        *result_size = 0;
        return NULL;
    }
    *result_size = heap->size;
    for (int i = heap->size - 1; i >= 0; i--) {
        result[i] = pop(heap);
    }
    free_heap(heap);
    return result;
}

int main() {
    Item dataset[] = {
        {1, 100}, {2, 500}, {3, 200}, {4, 800}, {5, 300},
        {6, 700}, {7, 400}, {8, 600}, {9, 50}, {10, 900}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;
    Item *expensive_items = find_n_expensive(dataset, dataset_size, n, &result_size);
    if (expensive_items) {
        for (int i = 0; i < result_size; i++) {
            printf("ID: %d, Price: %d\n", expensive_items[i].id, expensive_items[i].price);
        }
        free(expensive_items);
    }
    return 0;
}