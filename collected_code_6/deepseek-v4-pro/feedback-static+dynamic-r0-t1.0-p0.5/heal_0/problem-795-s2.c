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
} MaxHeap;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

MaxHeap *heap_create(int capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
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

void heap_destroy(MaxHeap *heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

void heapify_up(MaxHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[parent].price < heap->data[index].price) {
            swap(&heap->data[parent], &heap->data[index]);
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
            swap(&heap->data[largest], &heap->data[index]);
            index = largest;
        } else {
            break;
        }
    }
}

int heap_push(MaxHeap *heap, Item item) {
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = item;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

Item heap_pop(MaxHeap *heap) {
    Item top = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return top;
}

Item heap_peek(MaxHeap *heap) {
    return heap->data[0];
}

int find_n_cheapest(Item *dataset, int dataset_size, int n, Item *result) {
    if (dataset == NULL || result == NULL || n <= 0 || dataset_size <= 0) {
        return -1;
    }
    if (n > dataset_size) {
        n = dataset_size;
    }
    
    MaxHeap *heap = heap_create(n);
    if (heap == NULL) {
        return -1;
    }
    
    for (int i = 0; i < dataset_size; i++) {
        if (heap->size < n) {
            if (heap_push(heap, dataset[i]) != 0) {
                heap_destroy(heap);
                return -1;
            }
        } else if (dataset[i].price < heap_peek(heap).price) {
            heap_pop(heap);
            if (heap_push(heap, dataset[i]) != 0) {
                heap_destroy(heap);
                return -1;
            }
        }
    }
    
    int result_size = heap->size;
    for (int i = result_size - 1; i >= 0; i--) {
        result[i] = heap_pop(heap);
    }
    
    heap_destroy(heap);
    return result_size;
}

int main(void) {
    Item dataset[] = {
        {1, 45.99},
        {2, 12.50},
        {3, 78.30},
        {4, 23.75},
        {5, 5.99},
        {6, 67.20},
        {7, 34.60},
        {8, 89.99},
        {9, 15.40},
        {10, 56.80}
    };
    
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 4;
    Item *result = (Item *)malloc(sizeof(Item) * n);
    if (result == NULL) {
        return 1;
    }
    
    int count = find_n_cheapest(dataset, dataset_size, n, result);
    if (count < 0) {
        free(result);
        return 1;
    }
    
    printf("The %d cheapest items:\n", count);
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Price: %.2f\n", result[i].id, result[i].price);
    }
    
    free(result);
    return 0;
}