#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t id;
    const char *name;
    uint64_t price_cents;
} Item;

static int compare_items(const Item *left, const Item *right)
{
    if (left->price_cents < right->price_cents) {
        return -1;
    }
    if (left->price_cents > right->price_cents) {
        return 1;
    }
    if (left->id < right->id) {
        return -1;
    }
    if (left->id > right->id) {
        return 1;
    }
    return 0;
}

static int qsort_compare_items(const void *left, const void *right)
{
    return compare_items((const Item *)left, (const Item *)right);
}

static void swap_items(Item *left, Item *right)
{
    Item temporary = *left;
    *left = *right;
    *right = temporary;
}

static void max_heap_sift_up(Item *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (compare_items(&heap[parent], &heap[index]) >= 0) {
            break;
        }

        swap_items(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void max_heap_sift_down(Item *heap, size_t size, size_t index)
{
    for (;;) {
        size_t largest = index;
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;

        if (left < size &&
            compare_items(&heap[left], &heap[largest]) > 0) {
            largest = left;
        }

        if (right < size &&
            compare_items(&heap[right], &heap[largest]) > 0) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        swap_items(&heap[index], &heap[largest]);
        index = largest;
    }
}

bool find_n_cheapest(const Item *dataset,
                     size_t dataset_size,
                     size_t n,
                     Item **result,
                     size_t *result_size)
{
    Item *heap;
    size_t heap_size = 0;
    size_t i;

    if (result == NULL || result_size == NULL) {
        return false;
    }

    *result = NULL;
    *result_size = 0;

    if (dataset_size > 0 && dataset == NULL) {
        return false;
    }

    if (n == 0 || dataset_size == 0) {
        return true;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    if (n > SIZE_MAX / sizeof(*heap)) {
        return false;
    }

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        return false;
    }

    for (i = 0; i < dataset_size; ++i) {
        if (heap_size < n) {
            heap[heap_size] = dataset[i];
            max_heap_sift_up(heap, heap_size);
            ++heap_size;
        } else if (compare_items(&dataset[i], &heap[0]) < 0) {
            heap[0] = dataset[i];
            max_heap_sift_down(heap, heap_size, 0);
        }
    }

    qsort(heap, heap_size, sizeof(*heap), qsort_compare_items);

    *result = heap;
    *result_size = heap_size;
    return true;
}

int main(void)
{
    const Item dataset[] = {
        {1, "Laptop", 89999},
        {2, "Keyboard", 4599},
        {3, "Mouse", 2499},
        {4, "Monitor", 21999},
        {5, "USB Cable", 999},
        {6, "Headphones", 7999},
        {7, "Webcam", 5499},
        {8, "Phone Stand", 1499}
    };
    const size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    const size_t n = 3;
    Item *cheapest_items = NULL;
    size_t cheapest_count = 0;
    size_t i;

    if (!find_n_cheapest(dataset, dataset_size, n,
                         &cheapest_items, &cheapest_count)) {
        fputs("Unable to find the cheapest items.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < cheapest_count; ++i) {
        printf("%zu: %s - $%" PRIu64 ".%02" PRIu64 "\n",
               cheapest_items[i].id,
               cheapest_items[i].name,
               cheapest_items[i].price_cents / 100U,
               cheapest_items[i].price_cents % 100U);
    }

    free(cheapest_items);
    return EXIT_SUCCESS;
}