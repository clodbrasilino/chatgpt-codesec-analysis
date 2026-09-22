#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#define DATASET_SIZE 10
#define MAX_NAME_LEN 255

typedef struct {
    int id;
    char *name;
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MinHeap;

typedef struct {
    const char *name;
    double price;
} CatalogEntry;

static const CatalogEntry catalog[DATASET_SIZE] = {
    {"Laptop", 1299.99},
    {"Smartphone", 899.50},
    {"Headphones", 249.99},
    {"Monitor", 399.00},
    {"Keyboard", 129.99},
    {"Mouse", 59.99},
    {"Tablet", 549.00},
    {"Printer", 199.99},
    {"Camera", 749.99},
    {"Speaker", 89.99}
};

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL)
        return 0;
    while (len < max_len && s[len] != '\0')
        len++;
    return len;
}

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL)
        return NULL;
    len = bounded_strlen(src, (size_t)MAX_NAME_LEN + 1);
    if (len > MAX_NAME_LEN)
        return NULL;
    copy = (char *)malloc(len + 1);
    if (copy == NULL)
        return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static int item_init(Item *item, int id, const char *name, double price)
{
    if (item == NULL)
        return -1;
    item->id = id;
    item->name = duplicate_string(name);
    if (name != NULL && item->name == NULL)
        return -1;
    item->price = price;
    return 0;
}

static void item_destroy(Item *item)
{
    if (item == NULL)
        return;
    free(item->name);
    item->name = NULL;
}

static int item_copy(Item *dest, const Item *src)
{
    char *name_copy;

    if (dest == NULL || src == NULL)
        return -1;
    name_copy = duplicate_string(src->name);
    if (src->name != NULL && name_copy == NULL)
        return -1;
    dest->id = src->id;
    dest->name = name_copy;
    dest->price = src->price;
    return 0;
}

static void swap_items(Item *a, Item *b)
{
    Item temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MinHeap *heap, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        if (left < heap->size && heap->data[left].price < heap->data[smallest].price)
            smallest = left;
        if (right < heap->size && heap->data[right].price < heap->data[smallest].price)
            smallest = right;
        if (smallest == index)
            break;
        swap_items(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

static void heapify_up(MinHeap *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent].price <= heap->data[index].price)
            break;
        swap_items(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

static int heap_push(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size >= heap->capacity)
        return -1;
    if (item_copy(&heap->data[heap->size], item) != 0)
        return -1;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

static int heap_replace_root(MinHeap *heap, const Item *item)
{
    Item replacement;

    if (heap == NULL || item == NULL || heap->size == 0)
        return -1;
    if (item_copy(&replacement, item) != 0)
        return -1;
    item_destroy(&heap->data[0]);
    heap->data[0] = replacement;
    heapify_down(heap, 0);
    return 0;
}

size_t find_n_most_expensive(const Item *items, size_t count, size_t n, Item *result)
{
    MinHeap heap;
    size_t i;
    size_t result_count;

    if (items == NULL || result == NULL || count == 0 || n == 0)
        return 0;

    if (n > count)
        n = count;

    if (n > SIZE_MAX / sizeof(Item))
        return 0;

    heap.data = (Item *)malloc(n * sizeof(Item));
    if (heap.data == NULL)
        return 0;
    heap.size = 0;
    heap.capacity = n;

    for (i = 0; i < count; i++) {
        if (heap.size < heap.capacity) {
            if (heap_push(&heap, &items[i]) != 0) {
                while (heap.size > 0) {
                    heap.size--;
                    item_destroy(&heap.data[heap.size]);
                }
                free(heap.data);
                heap.data = NULL;
                return 0;
            }
        } else if (items[i].price > heap.data[0].price) {
            (void)heap_replace_root(&heap, &items[i]);
        }
    }

    result_count = heap.size;
    for (i = result_count; i > 0; i--) {
        result[i - 1] = heap.data[0];
        heap.size--;
        if (heap.size > 0) {
            heap.data[0] = heap.data[heap.size];
            heapify_down(&heap, 0);
        }
    }

    free(heap.data);
    heap.data = NULL;

    return result_count;
}

int main(int argc, const char *argv[])
{
    Item dataset[DATASET_SIZE];
    const size_t count = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;
    size_t alloc_size;
    size_t found = 0;
    size_t i;
    Item *result = NULL;
    int exit_code = EXIT_SUCCESS;

    for (i = 0; i < count; i++) {
        dataset[i].id = 0;
        dataset[i].name = NULL;
        dataset[i].price = 0.0;
    }

    for (i = 0; i < count; i++) {
        if (item_init(&dataset[i], (int)(i + 1), catalog[i].name, catalog[i].price) != 0) {
            fprintf(stderr, "Failed to initialize dataset\n");
            exit_code = EXIT_FAILURE;
            goto cleanup;
        }
    }

    if (argc > 1) {
        char *endptr = NULL;
        unsigned long long parsed;

        errno = 0;
        parsed = strtoull(argv[1], &endptr, 10);
        if (errno == 0 && endptr != argv[1] && *endptr == '\0' &&
            parsed > 0 && parsed <= (unsigned long long)SIZE_MAX)
            n = (size_t)parsed;
    }

    if (n > SIZE_MAX / sizeof(Item)) {
        fprintf(stderr, "Requested size is too large\n");
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    alloc_size = (n < count) ? n : count;
    result = (Item *)malloc(alloc_size * sizeof(Item));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    found = find_n_most_expensive(dataset, count, n, result);
    if (found == 0) {
        fprintf(stderr, "No items found\n");
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    printf("Top %zu most expensive items:\n", found);
    for (i = 0; i < found; i++) {
        printf("%zu. %s (ID: %d) - $%.2f\n",
               i + 1,
               (result[i].name != NULL) ? result[i].name : "",
               result[i].id, result[i].price);
    }

cleanup:
    if (result != NULL) {
        for (i = 0; i < found; i++)
            item_destroy(&result[i]);
        free(result);
        result = NULL;
    }
    for (i = 0; i < count; i++)
        item_destroy(&dataset[i]);

    return exit_code;
}