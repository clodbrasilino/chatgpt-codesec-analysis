#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double price;
} Item;

typedef struct {
    Item *data;
    int capacity;
    int size;
} MaxHeap;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

MaxHeap* create_heap(int capacity) {
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (!heap) return NULL;
    heap->data = (Item*)malloc(capacity * sizeof(Item));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void destroy_heap(MaxHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void heapify_up(MaxHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index].price > heap->data[parent].price) {
            swap(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MaxHeap *heap, int index) {
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
        if (largest != index) {
            swap(&heap->data[index], &heap->data[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void push_heap(MaxHeap *heap, Item item) {
    if (heap->size == heap->capacity) {
        if (item.price < heap->data[0].price) {
            heap->data[0] = item;
            heapify_down(heap, 0);
        }
    } else {
        heap->data[heap->size] = item;
        heapify_up(heap, heap->size);
        heap->size++;
    }
}

int find_cheapest_n(Item *dataset, int dataset_size, Item *result, int n) {
    if (n <= 0 || !dataset || !result || dataset_size <= 0) {
        return 0;
    }
    int target_n = n > dataset_size ? dataset_size : n;
    MaxHeap *heap = create_heap(target_n);
    if (!heap) {
        return 0;
    }
    for (int i = 0; i < dataset_size; i++) {
        push_heap(heap, dataset[i]);
    }
    for (int i = heap->size - 1; i >= 0; i--) {
        result[i] = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapify_down(heap, 0);
    }
    destroy_heap(heap);
    return target_n;
}

int main() {
    Item dataset[] = {
        {1, 19.99}, {2, 5.49}, {3, 12.50}, {4, 3.99},
        {5, 45.00}, {6, 8.75}, {7, 1.20}, {8, 22.30}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 4;
    Item *result = (Item*)malloc(n * sizeof(Item));
    if (!result) {
        return 1;
    }
    int found = find_cheapest_n(dataset, dataset_size, result, n);
    if (found > 0) {
        for (int i = 0; i < found; i++) {
            printf("ID: %d, Price: %.2f\n", result[i].id, result[i].price);
        }
    }
    free(result);
    return 0;
}