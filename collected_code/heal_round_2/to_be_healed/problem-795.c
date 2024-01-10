#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int price;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char name[101];    // increased size by 1 to account for possible null-terminator.
} Item;

typedef struct {
    Item* data;
    int size;
    int capacity;
} Heap;

void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left].price < heap->data[smallest].price)
        smallest = left;
    
    if (right < heap->size && heap->data[right].price < heap->data[smallest].price)
        smallest = right;
    
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));

    if(heap==NULL)   // Null check for malloc
        return heap;

    heap->data = (Item*)malloc(sizeof(Item) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insert(Heap* heap, Item item) {
    if (heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }

    int i = heap->size;

    if(heap->data==NULL)   // Null check for malloc
        return;

    heap->data[i] = item;

    while (i > 0 && heap->data[(i - 1) / 2].price > heap->data[i].price) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    heap->size++;
}

Item extractMin(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        Item emptyItem = {0, ""};
        return emptyItem;
    }

    Item min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return min;
}

void findNcheapItems(Item* dataset, int size, int n) {
    Heap* heap = createHeap(n);

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*heap.size' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of NULL 'heap' [CWE-476] [-Wanalyzer-null-dereference]
         */
        if (heap->size < n) {
            insert(heap, dataset[i]);
        }
        else if (dataset[i].price < heap->data[0].price) {
            extractMin(heap);
            insert(heap, dataset[i]);
        }
    }

    printf("N cheapest price items: \n");
    for (int i = 0; i < n; i++) {
        Item item = extractMin(heap);
        printf("Name: %s, Price: %d\n", item.name, item.price);
    }

    // Freeing the memory after use
    if(heap != NULL){
        free(heap->data);
        free(heap);
    }
}

int main() {
    Item dataset[] = {
        {100, "Item1"},
        {50, "Item2"},
        {200, "Item3"},
        {80, "Item4"},
        {120, "Item5"},
        {60, "Item6"},
        {150, "Item7"}
    };

    int size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;

    findNcheapItems(dataset, size, n);
    return 0;
}