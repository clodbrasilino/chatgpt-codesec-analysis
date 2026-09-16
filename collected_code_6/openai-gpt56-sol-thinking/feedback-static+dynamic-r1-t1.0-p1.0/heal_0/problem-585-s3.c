#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    const char *name;
    double price;
} Item;

static int compare_items(const Item *left, const Item *right)
{
    if (left->price < right->price) {
        return -1;
    }
    if (left->price > right->price) {
        return 1;
    }
    return strcmp(left->name, right->name);
}

static void swap_items(Item *left, Item *right)
{
    Item temporary = *left;
    *left = *right;
    *right = temporary;
}

static void sift_up(Item *heap, size_t index)
{
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (compare_items(&heap[index], &heap[parent]) >= 0) {
            break;
        }

        swap_items(&heap[index], &heap[parent]);
        index = parent;
    }
}

static void sift_down(Item *heap, size_t heap_size, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 1U) / 2U) {
            break;
        }

        left = (index * 2U) + 1U;
        right = left + 1U;

        if (left < heap_size &&
            compare_items(&heap[left], &heap[smallest]) < 0) {
            smallest = left;
        }

        if (right < heap_size &&
            compare_items(&heap[right], &heap[smallest]) < 0) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_items(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

bool find_n_most_expensive(const Item *items,
                           size_t item_count,
                           size_t n,
                           Item *result)
{
    Item *heap;
    size_t heap_size = 0U;
    size_t index;

    if (n > item_count) {
        return false;
    }

    if (item_count > 0U && items == NULL) {
        return false;
    }

    if (n > 0U && result == NULL) {
        return false;
    }

    if (n == 0U) {
        return true;
    }

    if (n > SIZE_MAX / sizeof(*heap)) {
        return false;
    }

    for (index = 0U; index < item_count; ++index) {
        if (items[index].name == NULL ||
            !isfinite(items[index].price) ||
            items[index].price < 0.0) {
            return false;
        }
    }

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        return false;
    }

    for (index = 0U; index < item_count; ++index) {
        if (heap_size < n) {
            heap[heap_size] = items[index];
            sift_up(heap, heap_size);
            ++heap_size;
        } else if (compare_items(&heap[0], &items[index]) < 0) {
            heap[0] = items[index];
            sift_down(heap, heap_size, 0U);
        }
    }

    for (heap_size = n; heap_size > 1U; --heap_size) {
        swap_items(&heap[0], &heap[heap_size - 1U]);
        sift_down(heap, heap_size - 1U, 0U);
    }

    memcpy(result, heap, n * sizeof(*result));
    free(heap);

    return true;
}

int main(void)
{
    const Item items[] = {
        {"Laptop", 1299.99},
        {"Smartphone", 899.50},
        {"Headphones", 199.99},
        {"Monitor", 549.75},
        {"Keyboard", 129.95},
        {"Camera", 1599.00},
        {"Tablet", 749.25},
        {"Printer", 349.80}
    };
    Item result[3];
    const size_t item_count = sizeof(items) / sizeof(items[0]);
    const size_t result_count = sizeof(result) / sizeof(result[0]);
    size_t index;

    if (!find_n_most_expensive(items, item_count, result_count, result)) {
        if (fprintf(stderr, "Unable to find the most expensive items.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (index = 0U; index < result_count; ++index) {
        if (printf("%zu. %s: $%.2f\n",
                   index + 1U,
                   result[index].name,
                   result[index].price) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}