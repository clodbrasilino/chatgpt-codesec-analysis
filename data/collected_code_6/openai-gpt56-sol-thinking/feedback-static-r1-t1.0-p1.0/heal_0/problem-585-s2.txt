#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    double price;
} Item;

typedef struct {
    size_t index;
    double price;
} PriceEntry;

static int is_worse(PriceEntry first, PriceEntry second)
{
    if (first.price < second.price) {
        return 1;
    }

    if (first.price > second.price) {
        return 0;
    }

    return first.index > second.index;
}

static void swap_entries(PriceEntry *first, PriceEntry *second)
{
    PriceEntry temporary = *first;
    *first = *second;
    *second = temporary;
}

static void sift_up(PriceEntry *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!is_worse(heap[index], heap[parent])) {
            break;
        }

        swap_entries(&heap[index], &heap[parent]);
        index = parent;
    }
}

static void sift_down(PriceEntry *heap, size_t size, size_t index)
{
    while (index < size / 2U) {
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;
        size_t worst = left;

        if (right < size && is_worse(heap[right], heap[left])) {
            worst = right;
        }

        if (!is_worse(heap[worst], heap[index])) {
            break;
        }

        swap_entries(&heap[index], &heap[worst]);
        index = worst;
    }
}

int find_n_most_expensive(
    const Item *items,
    size_t item_count,
    size_t n,
    PriceEntry **result,
    size_t *result_count)
{
    PriceEntry *heap = NULL;
    size_t heap_size = 0;
    size_t limit;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if (item_count > 0 && items == NULL) {
        return EINVAL;
    }

    for (i = 0; i < item_count; ++i) {
        if (items[i].name == NULL || !isfinite(items[i].price) ||
            items[i].price < 0.0) {
            return EDOM;
        }
    }

    limit = n < item_count ? n : item_count;

    if (limit == 0) {
        return 0;
    }

    if (limit > SIZE_MAX / sizeof(*heap)) {
        return EOVERFLOW;
    }

    heap = malloc(limit * sizeof(*heap));
    if (heap == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < item_count; ++i) {
        PriceEntry candidate = {i, items[i].price};

        if (heap_size < limit) {
            heap[heap_size] = candidate;
            sift_up(heap, heap_size);
            ++heap_size;
        } else if (is_worse(heap[0], candidate)) {
            heap[0] = candidate;
            sift_down(heap, heap_size, 0);
        }
    }

    for (i = heap_size; i > 1U; --i) {
        swap_entries(&heap[0], &heap[i - 1U]);
        sift_down(heap, i - 1U, 0);
    }

    *result = heap;
    *result_count = heap_size;

    return 0;
}

int main(void)
{
    const Item items[] = {
        {"Laptop", 1299.99},
        {"Smartphone", 899.50},
        {"Headphones", 249.95},
        {"Monitor", 579.00},
        {"Camera", 1499.00},
        {"Keyboard", 159.99},
        {"Television", 1899.99},
        {"Tablet", 749.00}
    };
    const size_t item_count = sizeof(items) / sizeof(items[0]);
    const size_t n = 3;
    PriceEntry *result = NULL;
    size_t result_count = 0;
    size_t i;
    int status;

    status = find_n_most_expensive(
        items,
        item_count,
        n,
        &result,
        &result_count
    );

    if (status != 0) {
        fprintf(stderr, "Unable to find items: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (printf("%zu. %s: %.2f\n",
                   i + 1U,
                   items[result[i].index].name,
                   result[i].price) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}