#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    size_t i;

    if (name == NULL || length == NULL) {
        return 0;
    }

    for (i = 0; i <= ITEM_NAME_MAX_LENGTH; ++i) {
        if (name[i] == '\0') {
            *length = i;
            return 1;
        }
    }

    return 0;
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

static char *copy_name(const char *name, size_t length)
{
    char *copy;
    size_t i;

    if (name == NULL || length > ITEM_NAME_MAX_LENGTH) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = name[i];
    }

    copy[length] = '\0';
    return copy;
}

static void free_item_results(ItemResult *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
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
    size_t heap_count = 0U;
    size_t initialized_count = 0U;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_count = 0U;

    if (n > item_count || (item_count > 0U && items == NULL)) {
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

    for (i = 0U; i < item_count; ++i) {
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
            sift_down(heap, heap_count, 0U);
        }
    }

    for (i = heap_count; i > 1U; --i) {
        swap_nodes(&heap[0], &heap[i - 1U]);
        sift_down(heap, i - 1U, 0U);
    }

    output = calloc(n, sizeof(*output));
    if (output == NULL) {
        free(heap);
        return FIND_ALLOCATION_FAILURE;
    }

    for (i = 0U; i < n; ++i) {
        output[i].name = copy_name(
            heap[i].item->name,
            heap[i].name_length
        );

        if (output[i].name == NULL) {
            free(heap);
            free_item_results(output, initialized_count);
            return FIND_ALLOCATION_FAILURE;
        }

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
    ItemResult *cheapest = NULL;
    size_t cheapest_count = 0U;
    FindStatus status;
    size_t i;

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

    for (i = 0U; i < cheapest_count; ++i) {
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