#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define ITEM_NAME_MAX_LENGTH 4096U

typedef struct {
    size_t id;
    const char *name;
    double price;
} Item;

typedef struct {
    size_t id;
    char *name;
    double price;
} ItemResult;

typedef struct {
    const Item *item;
    size_t source_index;
    size_t name_length;
} HeapNode;

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_INVALID_DATA,
    FIND_ALLOCATION_FAILURE
} FindStatus;

static int get_name_length(const char *name, size_t *length)
{
    const char *terminator;

    if (name == NULL || length == NULL) {
        return 0;
    }

    terminator = memchr(name, '\0', ITEM_NAME_MAX_LENGTH + 1U);
    if (terminator == NULL) {
        return 0;
    }

    *length = (size_t)(terminator - name);
    return 1;
}

static int compare_nodes(const HeapNode *left, const HeapNode *right)
{
    if (left->item->price < right->item->price) {
        return -1;
    }

    if (left->item->price > right->item->price) {
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
    while (index > 0) {
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
        size_t child = index * 2U + 1U;
        size_t right = child + 1U;

        if (right < count &&
            compare_nodes(&heap[right], &heap[child]) > 0) {
            child = right;
        }

        if (compare_nodes(&heap[index], &heap[child]) >= 0) {
            break;
        }

        swap_nodes(&heap[index], &heap[child]);
        index = child;
    }
}

static void free_item_results(ItemResult *items, size_t count)
{
    if (items == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(items[i].name);
    }

    free(items);
}

FindStatus find_n_cheapest(
    const Item *items,
    size_t item_count,
    size_t n,
    ItemResult **result,
    size_t *result_count)
{
    HeapNode *heap = NULL;
    ItemResult *output = NULL;
    size_t heap_count = 0;
    size_t initialized_count = 0;

    if (result == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0;

    if (n > item_count || (item_count > 0 && items == NULL)) {
        return FIND_INVALID_ARGUMENT;
    }

    if (n == 0) {
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

    for (size_t i = 0; i < item_count; ++i) {
        HeapNode candidate;
        size_t name_length;

        if (!get_name_length(items[i].name, &name_length) ||
            !isfinite(items[i].price) ||
            items[i].price < 0.0) {
            free(heap);
            return FIND_INVALID_DATA;
        }

        candidate.item = &items[i];
        candidate.source_index = i;
        candidate.name_length = name_length;

        if (heap_count < n) {
            heap[heap_count] = candidate;
            sift_up(heap, heap_count);
            ++heap_count;
        } else if (compare_nodes(&candidate, &heap[0]) < 0) {
            heap[0] = candidate;
            sift_down(heap, heap_count, 0);
        }
    }

    for (size_t end = heap_count; end > 1; --end) {
        swap_nodes(&heap[0], &heap[end - 1U]);
        sift_down(heap, end - 1U, 0);
    }

    output = calloc(n, sizeof(*output));
    if (output == NULL) {
        free(heap);
        return FIND_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        size_t allocation_size = heap[i].name_length + 1U;

        output[i].name = malloc(allocation_size);
        if (output[i].name == NULL) {
            free(heap);
            free_item_results(output, initialized_count);
            return FIND_ALLOCATION_FAILURE;
        }

        memcpy(output[i].name, heap[i].item->name, allocation_size);
        output[i].id = heap[i].item->id;
        output[i].price = heap[i].item->price;
        ++initialized_count;
    }

    free(heap);
    *result = output;
    *result_count = n;

    return FIND_SUCCESS;
}

int main(void)
{
    const Item dataset[] = {
        {1, "Laptop", 899.99},
        {2, "Keyboard", 49.95},
        {3, "Monitor", 229.50},
        {4, "Mouse", 24.99},
        {5, "Headphones", 79.90},
        {6, "USB Cable", 8.75},
        {7, "Webcam", 54.25},
        {8, "Desk Lamp", 31.40}
    };
    const size_t item_count = sizeof(dataset) / sizeof(dataset[0]);
    const size_t n = 3;
    ItemResult *cheapest = NULL;
    size_t cheapest_count = 0;
    FindStatus status;

    status = find_n_cheapest(
        dataset,
        item_count,
        n,
        &cheapest,
        &cheapest_count
    );

    if (status != FIND_SUCCESS) {
        fprintf(
            stderr,
            "Unable to find the cheapest items: error %d\n",
            (int)status
        );
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < cheapest_count; ++i) {
        printf(
            "%zu %s %.2f\n",
            cheapest[i].id,
            cheapest[i].name,
            cheapest[i].price
        );
    }

    free_item_results(cheapest, cheapest_count);
    return EXIT_SUCCESS;
}