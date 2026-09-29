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

    len = strnlen(name, MAX_NAME_LEN);
    if (len >= MAX_NAME_LEN) {
        return -1;
    }

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

static MinHeap *heap_create(size_t capacity)
{
    MinHeap *heap;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(Item)) {
        return NULL;
    }

    heap = malloc(sizeof(MinHeap));
    if (heap == NULL) {
        return NULL;
    }

    heap->data = malloc(capacity * sizeof(Item));
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

static void sift_up(MinHeap *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[index].price < heap->data[parent].price) {
            swap_items(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

static void sift_down(MinHeap *heap, size_t index)
{
    for (;;) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;

        if (left < heap->size &&
            heap->data[left].price < heap->data[smallest].price) {
            smallest = left;
        }
        if (right < heap->size &&
            heap->data[right].price < heap->data[smallest].price) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap_items(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

static int heap_push(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = *item;
    heap->data[heap->size].name[MAX_NAME_LEN - 1] = '\0';
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}

static int heap_pop(MinHeap *heap, Item *out)
{
    if (heap == NULL || out == NULL || heap->size == 0) {
        return -1;
    }
    *out = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    sift_down(heap, 0);
    return 0;
}

int find_n_cheapest(const Item *dataset, size_t dataset_size,
                    size_t n, Item *result)
{
    MinHeap *heap;
    size_t i;

    if (dataset == NULL || result == NULL ||
        dataset_size == 0 || n == 0 || n > dataset_size) {
        return -1;
    }

    heap = heap_create(dataset_size);
    if (heap == NULL) {
        return -1;
    }

    for (i = 0; i < dataset_size; i++) {
        if (heap_push(heap, &dataset[i]) != 0) {
            heap_destroy(heap);
            return -1;
        }
    }

    for (i = 0; i < n; i++) {
        if (heap_pop(heap, &result[i]) != 0) {
            heap_destroy(heap);
            return -1;
        }
    }

    heap_destroy(heap);
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
        {"Monitor", 249.99},
        {"Headset", 79.99},
        {"Webcam", 39.99},
        {"USB Cable", 9.99},
        {"Desk Lamp", 29.99}
    };
    size_t dataset_size = sizeof(raw_data) / sizeof(raw_data[0]);
    size_t n = 3;
    Item dataset[sizeof(raw_data) / sizeof(raw_data[0])];
    Item *result;
    size_t i;

    for (i = 0; i < dataset_size; i++) {
        if (item_set_name(&dataset[i], raw_data[i].name) != 0) {
            fprintf(stderr, "Item name too long or invalid\n");
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

    if (find_n_cheapest(dataset, dataset_size, n, result) != 0) {
        fprintf(stderr, "Failed to find cheapest items\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("The %zu cheapest items:\n", n);
    for (i = 0; i < n; i++) {
        printf("%.*s: $%.2f\n", MAX_NAME_LEN - 1, result[i].name,
               result[i].price);
    }

    free(result);
    return EXIT_SUCCESS;
}