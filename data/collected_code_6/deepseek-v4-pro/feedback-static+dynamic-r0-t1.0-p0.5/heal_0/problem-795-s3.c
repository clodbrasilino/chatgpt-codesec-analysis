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

MaxHeap* createHeap(int capacity) {
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

void destroyHeap(MaxHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void heapifyUp(MaxHeap *heap, int index) {
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

void heapifyDown(MaxHeap *heap, int index) {
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

void heapPush(MaxHeap *heap, Item item) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = item;
        heap->size++;
        heapifyUp(heap, heap->size - 1);
    } else if (item.price < heap->data[0].price) {
        heap->data[0] = item;
        heapifyDown(heap, 0);
    }
}

Item heapPop(MaxHeap *heap) {
    Item top = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return top;
}

int compareItems(const void *a, const void *b) {
    const Item *itemA = (const Item*)a;
    const Item *itemB = (const Item*)b;
    if (itemA->price < itemB->price) return -1;
    if (itemA->price > itemB->price) return 1;
    return 0;
}

Item* findNCheapestItems(Item *dataset, int datasetSize, int n, int *resultSize) {
    if (!dataset || datasetSize <= 0 || n <= 0) {
        *resultSize = 0;
        return NULL;
    }
    
    if (n > datasetSize) {
        n = datasetSize;
    }
    
    MaxHeap *heap = createHeap(n);
    if (!heap) {
        *resultSize = 0;
        return NULL;
    }
    
    for (int i = 0; i < datasetSize; i++) {
        heapPush(heap, dataset[i]);
    }
    
    Item *result = (Item*)malloc(sizeof(Item) * n);
    if (!result) {
        destroyHeap(heap);
        *resultSize = 0;
        return NULL;
    }
    
    *resultSize = n;
    for (int i = n - 1; i >= 0; i--) {
        result[i] = heapPop(heap);
    }
    
    qsort(result, n, sizeof(Item), compareItems);
    
    destroyHeap(heap);
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
    int datasetSize = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int resultSize = 0;
    
    Item *cheapest = findNCheapestItems(dataset, datasetSize, n, &resultSize);
    
    if (cheapest) {
        printf("The %d cheapest items:\n", resultSize);
        for (int i = 0; i < resultSize; i++) {
            printf("ID: %d, Price: %.2f\n", cheapest[i].id, cheapest[i].price);
        }
        free(cheapest);
    } else {
        printf("Failed to find cheapest items.\n");
    }
    
    return 0;
}