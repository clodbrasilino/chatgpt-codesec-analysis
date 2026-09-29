#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ITEM_NAME_MAX 64

typedef struct {
    int id;
    char name[ITEM_NAME_MAX];
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MinHeap;

static Item item_create(int id, const char *name, double price)
{
    Item item;
    int written;

    item.id = id;
    item.name[0] = '\0';
    if (name != NULL) {
        written = snprintf(item.name, sizeof(item.name), "%s", name);
        if (written < 0 || (size_t)written >= sizeof(item.name))
            item.name[sizeof(item.name) - 1] = '\0';
    }
    item.price = price;
    return item;
}

static void swap_items(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify_down(MinHeap *heap, size_t idx)
{
    for (;;) {
        size_t smallest = idx;
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;

        if (left < heap->size && heap->data[left].price < heap->data[smallest].price)
            smallest = left;
        if (right < heap->size && heap->data[right].price < heap->data[smallest].price)
            smallest = right;

        if (smallest == idx)
            break;

        swap_items(&heap->data[idx], &heap->data[smallest]);
        idx = smallest;
    }
}

static void heapify_up(MinHeap *heap, size_t idx)
{
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;

        if (heap->data[parent].price <= heap->data[idx].price)
            break;
        swap_items(&heap->data[parent], &heap->data[idx]);
        idx = parent;
    }
}

static int heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0)
        return -1;
    if (capacity > SIZE_MAX / sizeof(*heap->data))
        return -1;

    heap->data = (Item *)malloc(capacity * sizeof(*heap->data));
    if (heap->data == NULL)
        return -1;

    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static int heap_push(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL)
        return -1;
    if (heap->size >= heap->capacity)
        return -1;

    heap->data[heap->size] = *item;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

static int heap_replace_top(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size == 0)
        return -1;

    heap->data[0] = *item;
    heapify_down(heap, 0);
    return 0;
}

int find_n_most_expensive(const Item *items, size_t count, size_t n, Item *result)
{
    MinHeap heap;
    size_t i;

    if (items == NULL || result == NULL)
        return -1;
    if (n == 0 || count == 0 || n > count)
        return -1;

    if (heap_init(&heap, n) != 0)
        return -1;

    for (i = 0; i < n; i++) {
        if (heap_push(&heap, &items[i]) != 0) {
            heap_destroy(&heap);
            return -1;
        }
    }

    for (i = n; i < count; i++) {
        if (heap.size > 0 && items[i].price > heap.data[0].price) {
            if (heap_replace_top(&heap, &items[i]) != 0) {
                heap_destroy(&heap);
                return -1;
            }
        }
    }

    for (i = 0; i < heap.size; i++)
        result[i] = heap.data[i];

    heap_destroy(&heap);
    return 0;
}

static int compare_items_desc(const void *a, const void *b)
{
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;

    if (ia->price < ib->price)
        return 1;
    if (ia->price > ib->price)
        return -1;
    return 0;
}

int main(int argc, const char *argv[])
{
    Item dataset[] = {
        item_create(1,  "Laptop",        1299.99),
        item_create(2,  "Mouse",           25.50),
        item_create(3,  "Keyboard",        89.99),
        item_create(4,  "Monitor",        449.00),
        item_create(5,  "Headphones",     199.95),
        item_create(6,  "Webcam",          79.99),
        item_create(7,  "Printer",        329.50),
        item_create(8,  "USB Cable",        9.99),
        item_create(9,  "SSD Drive",      159.00),
        item_create(10, "Graphics Card",  899.00)
    };
    size_t count = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    Item *result;
    size_t i;

    if (argc > 1) {
        char *end = NULL;
        unsigned long val = strtoul(argv[1], &end, 10);

        if (end == argv[1] || *end != '\0' || val == 0 || val > SIZE_MAX) {
            fprintf(stderr, "Invalid item count: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
        n = (size_t)val;
    }

    if (n > count) {
        fprintf(stderr, "Requested count exceeds dataset size\n");
        return EXIT_FAILURE;
    }

    if (n > SIZE_MAX / sizeof(*result)) {
        fprintf(stderr, "Requested count is too large\n");
        return EXIT_FAILURE;
    }

    result = (Item *)malloc(n * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_n_most_expensive(dataset, count, n, result) != 0) {
        fprintf(stderr, "Failed to find top %zu items\n", n);
        free(result);
        result = NULL;
        return EXIT_FAILURE;
    }

    qsort(result, n, sizeof(*result), compare_items_desc);

    printf("Top %zu most expensive items:\n", n);
    for (i = 0; i < n; i++)
        printf("%d. %-15s $%.2f\n", result[i].id, result[i].name, result[i].price);

    free(result);
    result = NULL;
    return EXIT_SUCCESS;
}