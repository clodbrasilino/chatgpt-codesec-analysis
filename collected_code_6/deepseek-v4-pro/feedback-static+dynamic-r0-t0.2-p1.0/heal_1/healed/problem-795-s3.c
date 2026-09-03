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

MaxHeap* create_heap(int capacity) {
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (!heap) return NULL;
    heap->data = (Item*)malloc(sizeof(Item) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
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
            swap(&heap->data[index], &heap->data[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void heap_push(MaxHeap *heap, Item item) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = item;
        heapify_up(heap, heap->size);
        heap->size++;
    } else if (item.price < heap->data[0].price) {
        heap->data[0] = item;
        heapify_down(heap, 0);
    }
}

Item heap_pop(MaxHeap *heap) {
    Item top = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return top;
}

int compare_items(const void *a, const void *b) {
    const Item *item_a = (const Item*)a;
    const Item *item_b = (const Item*)b;
    if (item_a->price < item_b->price) return -1;
    if (item_a->price > item_b->price) return 1;
    return 0;
}

Item* find_n_cheapest(const Item *dataset, int dataset_size, int n, int *result_size) {
    if (!dataset || dataset_size <= 0 || n <= 0 || !result_size) {
        if (result_size) *result_size = 0;
        return NULL;
    }
    
    if (n > dataset_size) {
        n = dataset_size;
    }
    
    MaxHeap *heap = create_heap(n);
    if (!heap) {
        *result_size = 0;
        return NULL;
    }
    
    for (int i = 0; i < dataset_size; i++) {
        heap_push(heap, dataset[i]);
    }
    
    Item *result = (Item*)malloc(sizeof(Item) * n);
    if (!result) {
        destroy_heap(heap);
        *result_size = 0;
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        result[i] = heap_pop(heap);
    }
    
    qsort(result, n, sizeof(Item), compare_items);
    
    destroy_heap(heap);
    *result_size = n;
    return result;
}

int main(void) {
    Item dataset[] = {
        {1, 99.99},
        {2, 49.99},
        {3, 149.99},
        {4, 19.99},
        {5, 79.99},
        {6, 29.99},
        {7, 199.99},
        {8, 9.99}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;
    
    Item *cheapest = find_n_cheapest(dataset, dataset_size, n, &result_size);
    
    if (cheapest) {
        printf("The %d cheapest items:\n", result_size);
        for (int i = 0; i < result_size; i++) {
            printf("ID: %d, Price: %.2f\n", cheapest[i].id, cheapest[i].price);
        }
        free(cheapest);
    } else {
        printf("No items found or invalid input.\n");
    }
    
    return 0;
}