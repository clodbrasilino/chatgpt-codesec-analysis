#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define ITEM_NAME_CAPACITY 64U

typedef struct {
    size_t id;
    char name[ITEM_NAME_CAPACITY];
    double price;
} Item;

typedef struct {
    Item item;
    size_t source_index;
} HeapNode;

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_INVALID_DATA,
    FIND_ALLOCATION_FAILURE
} FindStatus;

static int item_is_valid(const Item *item)
{
    if (item == NULL) {
        return 0;
    }

    if (memchr(item->name, '\0', sizeof(item->name)) == NULL) {
        return 0;
    }

    if (!isfinite(item->price) || item->price < 0.0) {
        return 0;
    }

    return 1;
}

static int compare_nodes(const HeapNode *left, const HeapNode *right)
{
    if (left->item.price < right->item.price) {
        return -1;
    }

    if (left->item.price > right->item.price) {
        return 1;
    }

    if (left->source_index < right->source_index) {
        return -1;
    }

    if (left->source_index > right->source_index) {
        return 1;
    }

    return 0;
}

static void swap_nodes(HeapNode *left, HeapNode *right)
{
    HeapNode temporary = *left;
    *left = *right;
    *right = temporary;
}

static void sift_up(HeapNode *heap, size_t index)
{
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (compare_nodes(&heap[parent], &heap[index]) >= 0) {
            break;
        }

        swap_nodes(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void sift_down(HeapNode *heap, size_t count, size_t index)
{
    while (index < count / 2U) {
        size_t left_child = index * 2U + 1U;
        size_t right_child = left_child + 1U;
        size_t largest_child = left_child;

        if (right_child < count &&
            compare_nodes(&heap[right_child], &heap[left_child]) > 0) {
            largest_child = right_child;
        }

        if (compare_nodes(&heap[index], &heap[largest_child]) >= 0) {
            break;
        }

        swap_nodes(&heap[index], &heap[largest_child]);
        index = largest_child;
    }
}

FindStatus find_n_cheapest(
    const Item *items,
    size_t item_count,
    size_t n,
    Item **result,
    size_t *result_count)
{
    HeapNode *heap = NULL;
    Item *output = NULL;
    size_t heap_count = 0U;

    if (result == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0U;

    if ((item_count > 0U && items == NULL) || n > item_count) {
        return FIND_INVALID_ARGUMENT;
    }

    if (n == 0U) {
        return FIND_SUCCESS;
    }

    if (n > SIZE_MAX / sizeof(*heap) ||
        n > SIZE_MAX / sizeof(*output)) {
        return FIND_ALLOCATION_FAILURE;
    }

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        return FIND_ALLOCATION_FAILURE;
    }

    for (size_t i = 0U; i < item_count; ++i) {
        HeapNode candidate;

        if (!item_is_valid(&items[i])) {
            free(heap);
            return FIND_INVALID_DATA;
        }

        candidate.item = items[i];
        candidate.source_index = i;

        if (heap_count < n) {
            heap[heap_count] = candidate;
            sift_up(heap, heap_count);
            ++heap_count;
        } else if (compare_nodes(&candidate, &heap[0]) < 0) {
            heap[0] = candidate;
            sift_down(heap, heap_count, 0U);
        }
    }

    for (size_t end = heap_count; end > 1U; --end) {
        swap_nodes(&heap[0], &heap[end - 1U]);
        sift_down(heap, end - 1U, 0U);
    }

    output = malloc(n * sizeof(*output));
    if (output == NULL) {
        free(heap);
        return FIND_ALLOCATION_FAILURE;
    }

    for (size_t i = 0U; i < n; ++i) {
        output[i] = heap[i].item;
    }

    free(heap);

    *result = output;
    *result_count = n;

    return FIND_SUCCESS;
}

int main(void)
{
    const Item dataset[] = {
        {1U, "Laptop", 899.99},
        {2U, "Keyboard", 49.95},
        {3U, "Monitor", 229.50},
        {4U, "Mouse", 24.99},
        {5U, "Headphones", 79.90},
        {6U, "USB Cable", 8.75},
        {7U, "Webcam", 54.25},
        {8U, "Desk Lamp", 31.40}
    };

    const size_t item_count = sizeof(dataset) / sizeof(dataset[0]);
    const size_t n = 3U;
    Item *cheapest = NULL;
    size_t cheapest_count = 0U;

    FindStatus status = find_n_cheapest(
        dataset,
        item_count,
        n,
        &cheapest,
        &cheapest_count
    );

    if (status != FIND_SUCCESS) {
        fprintf(stderr, "Unable to find the cheapest items: error %d\n",
                (int)status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < cheapest_count; ++i) {
        printf(
            "%zu %.*s %.2f\n",
            cheapest[i].id,
            (int)(ITEM_NAME_CAPACITY - 1U),
            cheapest[i].name,
            cheapest[i].price
        );
    }

    free(cheapest);
    return EXIT_SUCCESS;
}