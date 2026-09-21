#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define ITEM_NAME_CAPACITY 64U
#define ITEM_NAME_MAX_LENGTH (ITEM_NAME_CAPACITY - 1U)

typedef struct {
    size_t id;
    char *name;
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

typedef struct {
    size_t id;
    const char *name;
    double price;
} ItemSeed;

static int get_name_length(const char *name, size_t *length)
{
    size_t i;

    if (name == NULL || length == NULL) {
        return 0;
    }

    for (i = 0U; i <= ITEM_NAME_MAX_LENGTH; ++i) {
        if (name[i] == '\0') {
            *length = i;
            return 1;
        }
    }

    return 0;
}

static FindStatus create_item(
    size_t id,
    const char *name,
    double price,
    Item *destination)
{
    char *name_copy;
    size_t name_length;
    size_t i;

    if (destination == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    if (!isfinite(price) || price < 0.0 ||
        !get_name_length(name, &name_length)) {
        return FIND_INVALID_DATA;
    }

    name_copy = malloc(name_length + 1U);
    if (name_copy == NULL) {
        return FIND_ALLOCATION_FAILURE;
    }

    for (i = 0U; i <= name_length; ++i) {
        name_copy[i] = name[i];
    }

    destination->id = id;
    destination->name = name_copy;
    destination->price = price;

    return FIND_SUCCESS;
}

static FindStatus copy_validated_item(
    const Item *source,
    Item *destination)
{
    if (source == NULL || destination == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    return create_item(
        source->id,
        source->name,
        source->price,
        destination
    );
}

static void destroy_item(Item *item)
{
    if (item == NULL) {
        return;
    }

    free(item->name);
    item->name = NULL;
    item->id = 0U;
    item->price = 0.0;
}

static void destroy_items(Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        destroy_item(&items[i]);
    }

    free(items);
}

static void destroy_heap(HeapNode *heap, size_t count)
{
    size_t i;

    if (heap == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        destroy_item(&heap[i].item);
    }

    free(heap);
}

static int compare_nodes(
    const HeapNode *left,
    const HeapNode *right)
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

static void sift_down(
    HeapNode *heap,
    size_t count,
    size_t index)
{
    while (index < count / 2U) {
        size_t left_child = index * 2U + 1U;
        size_t right_child = left_child + 1U;
        size_t largest_child = left_child;

        if (right_child < count &&
            compare_nodes(
                &heap[right_child],
                &heap[left_child]
            ) > 0) {
            largest_child = right_child;
        }

        if (compare_nodes(
                &heap[index],
                &heap[largest_child]
            ) >= 0) {
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
    size_t i;

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

    heap = calloc(n, sizeof(*heap));
    if (heap == NULL) {
        return FIND_ALLOCATION_FAILURE;
    }

    for (i = 0U; i < item_count; ++i) {
        HeapNode candidate = {0};
        FindStatus status;

        status = copy_validated_item(
            &items[i],
            &candidate.item
        );

        if (status != FIND_SUCCESS) {
            destroy_heap(heap, heap_count);
            return status;
        }

        candidate.source_index = i;

        if (heap_count < n) {
            heap[heap_count] = candidate;
            sift_up(heap, heap_count);
            ++heap_count;
        } else if (compare_nodes(&candidate, &heap[0]) < 0) {
            destroy_item(&heap[0].item);
            heap[0] = candidate;
            sift_down(heap, heap_count, 0U);
        } else {
            destroy_item(&candidate.item);
        }
    }

    for (i = heap_count; i > 1U; --i) {
        swap_nodes(&heap[0], &heap[i - 1U]);
        sift_down(heap, i - 1U, 0U);
    }

    output = calloc(n, sizeof(*output));
    if (output == NULL) {
        destroy_heap(heap, heap_count);
        return FIND_ALLOCATION_FAILURE;
    }

    for (i = 0U; i < n; ++i) {
        output[i] = heap[i].item;
        heap[i].item.name = NULL;
    }

    destroy_heap(heap, heap_count);

    *result = output;
    *result_count = n;

    return FIND_SUCCESS;
}

int main(void)
{
    static const ItemSeed seeds[] = {
        {1U, "Laptop", 899.99},
        {2U, "Keyboard", 49.95},
        {3U, "Monitor", 229.50},
        {4U, "Mouse", 24.99},
        {5U, "Headphones", 79.90},
        {6U, "USB Cable", 8.75},
        {7U, "Webcam", 54.25},
        {8U, "Desk Lamp", 31.40}
    };

    const size_t item_count = sizeof(seeds) / sizeof(seeds[0]);
    const size_t n = 3U;
    Item *dataset;
    Item *cheapest = NULL;
    size_t cheapest_count = 0U;
    FindStatus status;
    size_t i;

    if (item_count > SIZE_MAX / sizeof(*dataset)) {
        return EXIT_FAILURE;
    }

    dataset = calloc(item_count, sizeof(*dataset));
    if (dataset == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < item_count; ++i) {
        status = create_item(
            seeds[i].id,
            seeds[i].name,
            seeds[i].price,
            &dataset[i]
        );

        if (status != FIND_SUCCESS) {
            fprintf(
                stderr,
                "Unable to initialize items: error %d\n",
                (int)status
            );
            destroy_items(dataset, item_count);
            return EXIT_FAILURE;
        }
    }

    status = find_n_cheapest(
        dataset,
        item_count,
        n,
        &cheapest,
        &cheapest_count
    );

    destroy_items(dataset, item_count);

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

    destroy_items(cheapest, cheapest_count);

    return EXIT_SUCCESS;
}