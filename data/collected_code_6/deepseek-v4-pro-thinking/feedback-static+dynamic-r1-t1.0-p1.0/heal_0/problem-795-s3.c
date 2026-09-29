#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    int price;
} Item;

static void swap_items(Item *a, Item *b) {
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify_down(Item *heap, size_t size, size_t idx) {
    while (1) {
        size_t smallest = idx;
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;

        if (left < size && heap[left].price < heap[smallest].price) {
            smallest = left;
        }
        if (right < size && heap[right].price < heap[smallest].price) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }

        swap_items(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

int find_n_cheapest_items(const Item *dataset, size_t dataset_size, size_t n, Item *result) {
    if (dataset == NULL || result == NULL || dataset_size == 0 || n == 0 || n > dataset_size) {
        return -1;
    }

    Item *heap = (Item *)malloc(dataset_size * sizeof(*heap));
    if (heap == NULL) {
        return -1;
    }

    memcpy(heap, dataset, dataset_size * sizeof(*heap));

    for (size_t i = dataset_size / 2; i > 0; --i) {
        heapify_down(heap, dataset_size, i - 1);
    }

    for (size_t i = 0; i < n; ++i) {
        result[i] = heap[0];
        heap[0] = heap[dataset_size - i - 1];
        heapify_down(heap, dataset_size - i - 1, 0);
    }

    free(heap);
    return 0;
}

int main(void) {
    Item dataset[] = {
        {"laptop", 1200},
        {"mouse", 25},
        {"keyboard", 75},
        {"monitor", 300},
        {"usb cable", 10},
        {"webcam", 60}
    };

    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;

    Item *result = (Item *)malloc(n * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_n_cheapest_items(dataset, dataset_size, n, result) != 0) {
        fprintf(stderr, "Failed to find cheapest items\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        printf("%s: %d\n", result[i].name, result[i].price);
    }

    free(result);
    return EXIT_SUCCESS;
}