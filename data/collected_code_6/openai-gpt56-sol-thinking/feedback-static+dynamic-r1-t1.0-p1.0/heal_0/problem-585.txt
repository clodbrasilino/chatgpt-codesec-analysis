#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    size_t id;
    double price;
} Item;

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_INVALID_PRICE,
    FIND_ALLOCATION_FAILURE
} FindStatus;

static int item_is_worse(const Item *left, const Item *right)
{
    if (left->price < right->price) {
        return 1;
    }

    if (left->price > right->price) {
        return 0;
    }

    return left->id > right->id;
}

static void swap_items(Item *left, Item *right)
{
    Item temporary = *left;
    *left = *right;
    *right = temporary;
}

static void heap_sift_up(Item *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (!item_is_worse(&heap[index], &heap[parent])) {
            break;
        }

        swap_items(&heap[index], &heap[parent]);
        index = parent;
    }
}

static void heap_sift_down(Item *heap, size_t size, size_t index)
{
    for (;;) {
        size_t left;
        size_t right;
        size_t worst;

        if (index > (SIZE_MAX - 1) / 2) {
            break;
        }

        left = index * 2 + 1;
        if (left >= size) {
            break;
        }

        right = left + 1;
        worst = left;

        if (right < size && item_is_worse(&heap[right], &heap[left])) {
            worst = right;
        }

        if (!item_is_worse(&heap[worst], &heap[index])) {
            break;
        }

        swap_items(&heap[index], &heap[worst]);
        index = worst;
    }
}

static void heap_sort_descending(Item *heap, size_t size)
{
    size_t end;

    for (end = size; end > 1; --end) {
        swap_items(&heap[0], &heap[end - 1]);
        heap_sift_down(heap, end - 1, 0);
    }
}

FindStatus find_n_most_expensive(
    const Item *items,
    size_t item_count,
    size_t n,
    Item **result,
    size_t *result_count)
{
    Item *heap;
    size_t heap_size = 0;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    if ((item_count > 0 && items == NULL) || n > item_count) {
        return FIND_INVALID_ARGUMENT;
    }

    for (i = 0; i < item_count; ++i) {
        if (!isfinite(items[i].price) || items[i].price < 0.0) {
            return FIND_INVALID_PRICE;
        }
    }

    if (n == 0) {
        return FIND_SUCCESS;
    }

    if (n > SIZE_MAX / sizeof(*heap)) {
        return FIND_ALLOCATION_FAILURE;
    }

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        return FIND_ALLOCATION_FAILURE;
    }

    for (i = 0; i < item_count; ++i) {
        if (heap_size < n) {
            heap[heap_size] = items[i];
            heap_sift_up(heap, heap_size);
            ++heap_size;
        } else if (item_is_worse(&heap[0], &items[i])) {
            heap[0] = items[i];
            heap_sift_down(heap, heap_size, 0);
        }
    }

    heap_sort_descending(heap, heap_size);

    *result = heap;
    *result_count = heap_size;
    return FIND_SUCCESS;
}

int main(void)
{
    Item *items = NULL;
    Item *result = NULL;
    size_t item_count;
    size_t n;
    size_t result_count;
    size_t i;
    FindStatus status;

    if (scanf("%zu %zu", &item_count, &n) != 2) {
        fprintf(stderr, "Invalid item count or selection count.\n");
        return EXIT_FAILURE;
    }

    if (n > item_count) {
        fprintf(stderr, "Selection count exceeds item count.\n");
        return EXIT_FAILURE;
    }

    if (item_count > SIZE_MAX / sizeof(*items)) {
        fprintf(stderr, "Dataset is too large.\n");
        return EXIT_FAILURE;
    }

    if (item_count > 0) {
        items = malloc(item_count * sizeof(*items));
        if (items == NULL) {
            fprintf(stderr, "Unable to allocate dataset memory.\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < item_count; ++i) {
        items[i].id = i + 1;

        if (scanf("%lf", &items[i].price) != 1 ||
            !isfinite(items[i].price) ||
            items[i].price < 0.0) {
            fprintf(stderr, "Invalid price at item %zu.\n", i + 1);
            free(items);
            return EXIT_FAILURE;
        }
    }

    status = find_n_most_expensive(
        items,
        item_count,
        n,
        &result,
        &result_count);

    free(items);

    if (status != FIND_SUCCESS) {
        fprintf(stderr, "Unable to find the most expensive items.\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (printf("%zu %.2f\n", result[i].id, result[i].price) < 0) {
            fprintf(stderr, "Output failure.\n");
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}