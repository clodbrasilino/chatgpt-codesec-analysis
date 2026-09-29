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

MaxHeap *create_max_heap(int capacity) {
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

void destroy_max_heap(MaxHeap *heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

void max_heapify_down(MaxHeap *heap, int index) {
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
        max_heapify_down(heap, largest);
    }
}

void max_heapify_up(MaxHeap *heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->data[parent].price < heap->data[index].price) {
        swap(&heap->data[parent], &heap->data[index]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

int max_heap_push(MaxHeap *heap, Item item) {
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = item;
    max_heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

Item max_heap_pop(MaxHeap *heap) {
    Item top = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    max_heapify_down(heap, 0);
    return top;
}

Item max_heap_peek(MaxHeap *heap) {
    return heap->data[0];
}

int compare_items(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'item_a' can be declared as pointer to const [constVariablePointer]
     */
    Item *item_a = (Item *)a;
    /* Possible weaknesses found:
     *  Variable 'item_b' can be declared as pointer to const [constVariablePointer]
     */
    Item *item_b = (Item *)b;
    if (item_a->price < item_b->price) return -1;
    if (item_a->price > item_b->price) return 1;
    return 0;
}

Item *find_n_cheapest(Item *dataset, int dataset_size, int n, int *result_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_size==NULL' is not redundant
     */
    if (dataset == NULL || dataset_size <= 0 || n <= 0 || result_size == NULL) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'result_size==NULL' is redundant or there is possible null pointer dereference: result_size. [nullPointerRedundantCheck]
         */
        *result_size = 0;
        return NULL;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    MaxHeap *heap = create_max_heap(n);
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < dataset_size; i++) {
        if (heap->size < n) {
            if (max_heap_push(heap, dataset[i]) != 0) {
                destroy_max_heap(heap);
                *result_size = 0;
                return NULL;
            }
        } else if (dataset[i].price < max_heap_peek(heap).price) {
            max_heap_pop(heap);
            if (max_heap_push(heap, dataset[i]) != 0) {
                destroy_max_heap(heap);
                *result_size = 0;
                return NULL;
            }
        }
    }

    Item *result = (Item *)malloc(sizeof(Item) * heap->size);
    if (result == NULL) {
        destroy_max_heap(heap);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < heap->size; i++) {
        result[i] = heap->data[i];
    }

    *result_size = heap->size;
    destroy_max_heap(heap);

    qsort(result, *result_size, sizeof(Item), compare_items);

    return result;
}

int main(void) {
    Item dataset[] = {
        {1, 25.50},
        {2, 10.00},
        {3, 45.75},
        {4, 5.25},
        {5, 30.00},
        {6, 15.50},
        {7, 20.00},
        {8, 8.75}
    };
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;

    Item *cheapest = find_n_cheapest(dataset, dataset_size, n, &result_size);

    if (cheapest != NULL) {
        printf("The %d cheapest items:\n", result_size);
        for (int i = 0; i < result_size; i++) {
            printf("ID: %d, Price: %.2f\n", cheapest[i].id, cheapest[i].price);
        }
        free(cheapest);
    } else {
        printf("Failed to find cheapest items.\n");
    }

    return 0;
}