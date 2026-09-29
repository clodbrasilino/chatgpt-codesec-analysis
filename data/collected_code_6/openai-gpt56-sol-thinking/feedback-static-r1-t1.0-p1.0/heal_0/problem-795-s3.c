#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t id;
    uint64_t price_cents;
} Item;

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_OUT_OF_MEMORY
} FindStatus;

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

static void swap_items(Item *left, Item *right)
{
    Item temporary = *left;
    *left = *right;
    *right = temporary;
}

static void max_heap_sift_down(Item *heap, size_t count, size_t root)
{
    while (root < count / 2U) {
        size_t child = root * 2U + 1U;

        if (child + 1U < count &&
            compare_items(&heap[child], &heap[child + 1U]) < 0) {
            ++child;
        }

        if (compare_items(&heap[root], &heap[child]) >= 0) {
            break;
        }

        swap_items(&heap[root], &heap[child]);
        root = child;
    }
}

static void build_max_heap(Item *heap, size_t count)
{
    size_t index;

    for (index = count / 2U; index > 0U; --index) {
        max_heap_sift_down(heap, count, index - 1U);
    }
}

static void sort_max_heap(Item *heap, size_t count)
{
    size_t remaining;

    for (remaining = count; remaining > 1U; --remaining) {
        swap_items(&heap[0], &heap[remaining - 1U]);
        max_heap_sift_down(heap, remaining - 1U, 0U);
    }
}

FindStatus find_n_cheapest(const Item *items,
                           size_t item_count,
                           size_t n,
                           Item **result,
                           size_t *result_count)
{
    Item *heap;
    size_t index;

    if (result == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0U;

    if ((items == NULL && item_count != 0U) || n > item_count) {
        return FIND_INVALID_ARGUMENT;
    }

    if (n == 0U) {
        return FIND_SUCCESS;
    }

    if (n > SIZE_MAX / sizeof(*heap)) {
        return FIND_OUT_OF_MEMORY;
    }

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        return FIND_OUT_OF_MEMORY;
    }

    for (index = 0U; index < n; ++index) {
        heap[index] = items[index];
    }

    build_max_heap(heap, n);

    for (index = n; index < item_count; ++index) {
        if (compare_items(&items[index], &heap[0]) < 0) {
            heap[0] = items[index];
            max_heap_sift_down(heap, n, 0U);
        }
    }

    sort_max_heap(heap, n);

    *result = heap;
    *result_count = n;
    return FIND_SUCCESS;
}

int main(void)
{
    const Item dataset[] = {
        {101U, 1599U},
        {102U, 499U},
        {103U, 1299U},
        {104U, 250U},
        {105U, 899U},
        {106U, 499U},
        {107U, 1999U},
        {108U, 349U}
    };
    const size_t item_count = sizeof(dataset) / sizeof(dataset[0]);
    const size_t requested_count = 4U;
    Item *cheapest = NULL;
    size_t cheapest_count = 0U;
    size_t index;
    FindStatus status;

    status = find_n_cheapest(dataset,
                             item_count,
                             requested_count,
                             &cheapest,
                             &cheapest_count);

    if (status != FIND_SUCCESS) {
        if (fprintf(stderr, "Unable to find the cheapest items\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (index = 0U; index < cheapest_count; ++index) {
        if (printf("Item %" PRIu64 ": $%" PRIu64 ".%02" PRIu64 "\n",
                   cheapest[index].id,
                   cheapest[index].price_cents / 100U,
                   cheapest[index].price_cents % 100U) < 0) {
            free(cheapest);
            return EXIT_FAILURE;
        }
    }

    free(cheapest);
    return EXIT_SUCCESS;
}