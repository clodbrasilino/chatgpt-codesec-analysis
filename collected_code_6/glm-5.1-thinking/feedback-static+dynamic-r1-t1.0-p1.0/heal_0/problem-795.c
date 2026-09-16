#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double price;
} Item;

void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify_down(Item *heap, int size, int index) {
    while (1) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left].price > heap[largest].price) {
            largest = left;
        }
        if (right < size && heap[right].price > heap[largest].price) {
            largest = right;
        }
        if (largest != index) {
            swap(&heap[index], &heap[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void max_heapify_up(Item *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].price > heap[parent].price) {
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

Item* find_n_cheapest(Item *dataset, int dataset_size, int n, int *result_size) {
    if (dataset == NULL || result_size == NULL || n <= 0 || dataset_size <= 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    Item *heap = (Item*)malloc(n * sizeof(Item));
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    int heap_size = 0;

    for (int i = 0; i < dataset_size; i++) {
        if (heap_size < n) {
            heap[heap_size] = dataset[i];
            max_heapify_up(heap, heap_size);
            heap_size++;
        } else {
            if (dataset[i].price < heap[0].price) {
                heap[0] = dataset[i];
                max_heapify_down(heap, heap_size, 0);
            }
        }
    }

    Item *result = (Item*)malloc(n * sizeof(Item));
    if (result == NULL) {
        free(heap);
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        result[i] = heap[i];
    }

    free(heap);
    *result_size = n;
    return result;
}

int main() {
    Item dataset[] = {
        {1, 19.99},
        {2, 5.49},
        {3, 12.50},
        {4, 1.99},
        {5, 8.75},
        {6, 3.20},
        {7, 25.00},
        {8, 0.99}
    };
    
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;

    Item *cheapest_items = find_n_cheapest(dataset, dataset_size, n, &result_size);

    if (cheapest_items != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("Item ID: %d, Price: %.2f\n", cheapest_items[i].id, cheapest_items[i].price);
        }
        free(cheapest_items);
    }

    return 0;
}