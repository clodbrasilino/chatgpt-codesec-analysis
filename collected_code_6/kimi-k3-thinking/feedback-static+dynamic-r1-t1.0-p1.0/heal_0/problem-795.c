#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int id;
    double price;
} Item;

static void swap_items(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static void max_heapify_down(Item *heap, size_t heap_size, size_t index)
{
    size_t largest;
    size_t left;
    size_t right;

    for (;;) {
        largest = index;
        left = 2u * index + 1u;
        right = 2u * index + 2u;

        if (left < heap_size && heap[left].price > heap[largest].price) {
            largest = left;
        }
        if (right < heap_size && heap[right].price > heap[largest].price) {
            largest = right;
        }
        if (largest == index) {
            break;
        }
        swap_items(&heap[index], &heap[largest]);
        index = largest;
    }
}

static void build_max_heap(Item *heap, size_t heap_size)
{
    size_t i;

    if (heap_size < 2u) {
        return;
    }
    for (i = heap_size / 2u; i > 0u; --i) {
        max_heapify_down(heap, heap_size, i - 1u);
    }
}

static void heap_sort_ascending(Item *heap, size_t heap_size)
{
    size_t end;

    for (end = heap_size; end > 1u; --end) {
        swap_items(&heap[0], &heap[end - 1u]);
        max_heapify_down(heap, end - 1u, 0u);
    }
}

Item *find_n_cheapest(const Item *items, size_t item_count, size_t n, size_t *out_count)
{
    Item *heap;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0u;

    if (items == NULL || item_count == 0u || n == 0u) {
        return NULL;
    }
    if (n > item_count) {
        n = item_count;
    }
    if (n > SIZE_MAX / sizeof(Item)) {
        return NULL;
    }

    heap = (Item *)malloc(n * sizeof(Item));
    if (heap == NULL) {
        return NULL;
    }

    for (i = 0u; i < n; ++i) {
        heap[i] = items[i];
    }
    build_max_heap(heap, n);

    for (i = n; i < item_count; ++i) {
        if (items[i].price < heap[0].price) {
            heap[0] = items[i];
            max_heapify_down(heap, n, 0u);
        }
    }

    *out_count = n;
    return heap;
}

int main(void)
{
    Item dataset[] = {
        {1, 19.99},
        {2, 5.49},
        {3, 12.75},
        {4, 3.99},
        {5, 25.00},
        {6, 7.25},
        {7, 1.50},
        {8, 14.40},
        {9, 9.99},
        {10, 4.75},
        {11, 22.10},
        {12, 6.30}
    };
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 5u;
    size_t result_count = 0u;
    size_t i;
    Item *cheapest;

    cheapest = find_n_cheapest(dataset, dataset_size, n, &result_count);
    if (cheapest == NULL || result_count == 0u) {
        fprintf(stderr, "Error: unable to compute the cheapest items.\n");
        free(cheapest);
        return EXIT_FAILURE;
    }

    heap_sort_ascending(cheapest, result_count);

    printf("The %zu cheapest items:\n", result_count);
    for (i = 0u; i < result_count; ++i) {
        printf("Item %d: $%.2f\n", cheapest[i].id, cheapest[i].price);
    }

    free(cheapest);
    cheapest = NULL;

    return EXIT_SUCCESS;
}