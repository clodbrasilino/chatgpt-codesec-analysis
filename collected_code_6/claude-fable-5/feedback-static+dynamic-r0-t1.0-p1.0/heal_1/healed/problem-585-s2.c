#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME_LEN 64

typedef struct {
    char name[MAX_NAME_LEN];
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MinHeap;

static int item_set_name(Item *item, const char *name)
{
    size_t len;

    if (item == NULL || name == NULL) {
        return -1;
    }
    len = strlen(name);
    if (len >= MAX_NAME_LEN) {
        return -1;
    }
    memcpy(item->name, name, len);
    item->name[len] = '\0';
    return 0;
}

static int heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0 ||
        capacity > SIZE_MAX / sizeof(Item)) {
        return -1;
    }
    heap->data = malloc(capacity * sizeof(Item));
    if (heap->data == NULL) {
        return -1;
    }
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

static void heap_swap(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_sift_up(MinHeap *heap, size_t idx)
{
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap->data[idx].price < heap->data[parent].price) {
            heap_swap(&heap->data[idx], &heap->data[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

static void heap_sift_down(MinHeap *heap, size_t idx)
{
    for (;;) {
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;
        size_t smallest = idx;

        if (left < heap->size &&
            heap->data[left].price < heap->data[smallest].price) {
            smallest = left;
        }
        if (right < heap->size &&
            heap->data[right].price < heap->data[smallest].price) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        heap_swap(&heap->data[idx], &heap->data[smallest]);
        idx = smallest;
    }
}

static int heap_push(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = *item;
    heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}

static int heap_replace_root(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size == 0) {
        return -1;
    }
    heap->data[0] = *item;
    heap_sift_down(heap, 0);
    return 0;
}

static int compare_price_desc(const void *a, const void *b)
{
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;
    if (ia->price < ib->price) {
        return 1;
    }
    if (ia->price > ib->price) {
        return -1;
    }
    return 0;
}

static int find_n_expensive(const Item *items, size_t count, size_t n,
                            Item *result, size_t result_capacity,
                            size_t *result_count)
{
    MinHeap heap;
    size_t i;

    if (items == NULL || result == NULL || result_count == NULL ||
        n == 0 || count == 0 || result_capacity == 0) {
        return -1;
    }

    if (n > count) {
        n = count;
    }

    if (n > result_capacity) {
        return -1;
    }

    if (heap_init(&heap, n) != 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (heap.size < heap.capacity) {
            if (heap_push(&heap, &items[i]) != 0) {
                heap_destroy(&heap);
                return -1;
            }
        } else if (items[i].price > heap.data[0].price) {
            if (heap_replace_root(&heap, &items[i]) != 0) {
                heap_destroy(&heap);
                return -1;
            }
        }
    }

    if (heap.size > result_capacity) {
        heap_destroy(&heap);
        return -1;
    }

    memcpy(result, heap.data, heap.size * sizeof(Item));
    *result_count = heap.size;

    qsort(result, *result_count, sizeof(Item), compare_price_desc);

    heap_destroy(&heap);
    return 0;
}

int main(void)
{
    static const struct {
        const char *name;
        double price;
    } raw_data[] = {
        {"Laptop", 1299.99},
        {"Phone", 899.50},
        {"Monitor", 349.00},
        {"Keyboard", 79.99},
        {"Mouse", 29.99},
        {"Headphones", 199.99},
        {"Tablet", 649.00},
        {"Camera", 1099.00},
        {"Printer", 249.50},
        {"Speaker", 149.99}
    };
    size_t count = sizeof(raw_data) / sizeof(raw_data[0]);
    size_t n = 3;
    Item dataset[sizeof(raw_data) / sizeof(raw_data[0])];
    Item *result;
    size_t result_count = 0;
    size_t i;

    for (i = 0; i < count; i++) {
        if (item_set_name(&dataset[i], raw_data[i].name) != 0) {
            fprintf(stderr, "Item name too long\n");
            return EXIT_FAILURE;
        }
        dataset[i].price = raw_data[i].price;
    }

    if (n > SIZE_MAX / sizeof(Item)) {
        fprintf(stderr, "Requested size too large\n");
        return EXIT_FAILURE;
    }

    result = malloc(n * sizeof(Item));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_n_expensive(dataset, count, n, result, n, &result_count) != 0) {
        fprintf(stderr, "Failed to find expensive items\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Top %zu most expensive items:\n", result_count);
    for (i = 0; i < result_count; i++) {
        printf("%.*s: %.2f\n", MAX_NAME_LEN, result[i].name, result[i].price);
    }

    free(result);
    return EXIT_SUCCESS;
}