#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ITEM_NAME_MAX 64

typedef struct {
    char name[ITEM_NAME_MAX];
    double price;
} Item;

static int set_item_name(Item *item, const char *name)
{
    if (item == NULL || name == NULL) {
        return -1;
    }
    size_t len = strnlen(name, sizeof(item->name));
    if (len >= sizeof(item->name)) {
        return -1;
    }
    memcpy(item->name, name, len);
    item->name[len] = '\0';
    return 0;
}

static void swap_items(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_down(Item *heap, size_t size, size_t idx)
{
    for (;;) {
        size_t smallest = idx;
        size_t left = 2U * idx + 1U;
        size_t right = 2U * idx + 2U;

        if (left < size && heap[left].price < heap[smallest].price) {
            smallest = left;
        }
        if (right < size && heap[right].price < heap[smallest].price) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        swap_items(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

static void build_min_heap(Item *heap, size_t size)
{
    if (size < 2U) {
        return;
    }
    for (size_t i = size / 2U; i > 0U; i--) {
        sift_down(heap, size, i - 1U);
    }
}

static int find_n_cheapest(const Item *items, size_t count, size_t n,
                           Item *result, size_t result_capacity)
{
    if (items == NULL || result == NULL || n == 0U || n > count ||
        n > result_capacity) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(Item)) {
        return -1;
    }

    size_t total_bytes = count * sizeof(Item);

    Item *heap = malloc(total_bytes);
    if (heap == NULL) {
        return -1;
    }

    memcpy(heap, items, total_bytes);
    build_min_heap(heap, count);

    size_t heap_size = count;
    for (size_t i = 0U; i < n; i++) {
        result[i] = heap[0];
        heap_size--;
        heap[0] = heap[heap_size];
        sift_down(heap, heap_size, 0U);
    }

    free(heap);
    return 0;
}

int main(void)
{
    static const struct {
        const char *name;
        double price;
    } raw_data[] = {
        {"Laptop", 999.99},
        {"Mouse", 19.99},
        {"Keyboard", 49.99},
        {"Monitor", 199.99},
        {"USB Cable", 5.99},
        {"Headphones", 89.99},
        {"Webcam", 39.99},
        {"Desk Lamp", 24.99}
    };

    size_t count = sizeof(raw_data) / sizeof(raw_data[0]);
    size_t n = 3U;

    if (count > SIZE_MAX / sizeof(Item) || n > SIZE_MAX / sizeof(Item)) {
        fprintf(stderr, "Size overflow\n");
        return EXIT_FAILURE;
    }

    Item *dataset = malloc(count * sizeof(Item));
    if (dataset == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; i++) {
        if (set_item_name(&dataset[i], raw_data[i].name) != 0) {
            fprintf(stderr, "Item name too long\n");
            free(dataset);
            return EXIT_FAILURE;
        }
        dataset[i].price = raw_data[i].price;
    }

    Item *cheapest = malloc(n * sizeof(Item));
    if (cheapest == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(dataset);
        return EXIT_FAILURE;
    }

    if (find_n_cheapest(dataset, count, n, cheapest, n) != 0) {
        fprintf(stderr, "Failed to find cheapest items\n");
        free(cheapest);
        free(dataset);
        return EXIT_FAILURE;
    }

    printf("The %zu cheapest items are:\n", n);
    for (size_t i = 0U; i < n; i++) {
        printf("%s: $%.2f\n", cheapest[i].name, cheapest[i].price);
    }

    free(cheapest);
    free(dataset);
    return EXIT_SUCCESS;
}