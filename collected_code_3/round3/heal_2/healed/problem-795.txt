#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int id;
} Item;

typedef struct {
    Item* items;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)calloc(1, sizeof(Heap));
    if (!heap) return NULL;
    heap->capacity = capacity;
    heap->items = (Item*)calloc(capacity, sizeof(Item));
    if (!heap->items) {
        free(heap);
        return NULL;
    }
    return heap;
}

void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->items[left].price > heap->items[largest].price)
        largest = left;

    if (right < heap->size && heap->items[right].price > heap->items[largest].price)
        largest = right;

    if (largest != i) {
        swap(&heap->items[i], &heap->items[largest]);
        heapify(heap, largest);
    }
}

void insert(Heap* heap, Item item) {
    if (heap->size < heap->capacity) {
        heap->items[heap->size++] = item;
        for (int i = heap->size / 2 - 1; i >= 0; i--)
            heapify(heap, i);
    } else if (item.price < heap->items[0].price) {
        heap->items[0] = item;
        heapify(heap, 0);
    }
}

int main() {
    int n, size;
    printf("Enter the number of items: ");
    scanf("%d", &size);

    printf("Enter the number of cheap items to find: ");
    scanf("%d", &n);

    Heap* heap = createHeap(n);
    if (!heap) return EXIT_FAILURE;

    Item* items = (Item*)calloc(size, sizeof(Item));
    if (!items) {
        free(heap->items);
        free(heap);
        return EXIT_FAILURE;
    }

    printf("Enter the prices and ids of the items:\n");
    for (int i = 0; i < size; i++)
        scanf("%d %d", &items[i].price, &items[i].id);

    for (int i = 0; i < size; i++)
        insert(heap, items[i]);

    printf("The ids of the %d cheapest items are:\n", n);
    for (int i = 0; i < n; i++)
        printf("%d\n", heap->items[i].id);

    free(heap->items);
    free(heap);
    free(items);

    return 0;
}