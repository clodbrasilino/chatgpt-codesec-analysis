#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ITEM_NAME_SIZE 32

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[ITEM_NAME_SIZE];
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MinHeap;

static int item_init(Item *item, int id, const char *name, double price)
{
    int written;

    if (item == NULL) {
        return -1;
    }

    item->id = id;
    item->price = price;
    memset(item->name, 0, sizeof(item->name));

    if (name == NULL) {
        return 0;
    }

    written = snprintf(item->name, sizeof(item->name), "%s", name);
    if (written < 0) {
        memset(item->name, 0, sizeof(item->name));
        return -1;
    }
    item->name[sizeof(item->name) - 1] = '\0';

    return 0;
}

static void swap_items(Item *a, Item *b)
{
    Item temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(Item)) {
        return -1;
    }
    heap->data = (Item *)malloc(capacity * sizeof(Item));
    if (heap->data == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap == NULL) {
        return;
    }
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void heapify_down(MinHeap *heap, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

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

static void heapify_up(MinHeap *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap->data[parent].price <= heap->data[index].price) {
            break;
        }
        swap_items(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

static int heap_push(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = *item;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

static int heap_pop_min(MinHeap *heap, Item *item)
{
    if (heap == NULL || item == NULL || heap->size == 0) {
        return -1;
    }
    *item = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        heapify_down(heap, 0);
    }
    return 0;
}

static int heap_replace_min(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size == 0) {
        return -1;
    }
    heap->data[0] = *item;
    heapify_down(heap, 0);
    return 0;
}

int find_n_most_expensive(const Item *items, size_t count, size_t n,
                          Item *result, size_t *result_count)
{
    MinHeap heap;
    size_t i;
    size_t heap_capacity;
    size_t out_index;

    if (items == NULL || result == NULL || result_count == NULL) {
        return -1;
    }
    *result_count = 0;
    if (n == 0 || count == 0) {
        return 0;
    }

    heap_capacity = (n < count) ? n : count;

    if (heap_init(&heap, heap_capacity) != 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (heap.size < heap.capacity) {
            if (heap_push(&heap, &items[i]) != 0) {
                heap_destroy(&heap);
                return -1;
            }
        } else if (items[i].price > heap.data[0].price) {
            if (heap_replace_min(&heap, &items[i]) != 0) {
                heap_destroy(&heap);
                return -1;
            }
        }
    }

    out_index = heap.size;
    while (heap.size > 0) {
        out_index--;
        if (heap_pop_min(&heap, &result[out_index]) != 0) {
            heap_destroy(&heap);
            return -1;
        }
        (*result_count)++;
    }

    heap_destroy(&heap);
    return 0;
}

int main(void)
{
    Item items[8];
    size_t count = sizeof(items) / sizeof(items[0]);
    size_t n = 3;
    size_t result_count = 0;
    size_t i;
    Item *result;

    if (item_init(&items[0], 1, "Keyboard", 49.99) != 0 ||
        item_init(&items[1], 2, "Mouse", 25.50) != 0 ||
        item_init(&items[2], 3, "Monitor", 199.99) != 0 ||
        item_init(&items[3], 4, "Laptop", 1299.00) != 0 ||
        item_init(&items[4], 5, "Headphones", 89.95) != 0 ||
        item_init(&items[5], 6, "Webcam", 59.99) != 0 ||
        item_init(&items[6], 7, "Printer", 249.75) != 0 ||
        item_init(&items[7], 8, "USB Cable", 9.99) != 0) {
        fprintf(stderr, "Error: failed to initialize items\n");
        return EXIT_FAILURE;
    }

    if (n > SIZE_MAX / sizeof(Item)) {
        fprintf(stderr, "Error: requested count too large\n");
        return EXIT_FAILURE;
    }

    result = (Item *)malloc(n * sizeof(Item));
    if (result == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_n_most_expensive(items, count, n, result, &result_count) != 0) {
        fprintf(stderr, "Error: failed to find expensive items\n");
        free(result);
        result = NULL;
        return EXIT_FAILURE;
    }

    printf("Top %zu most expensive items:\n", result_count);
    for (i = 0; i < result_count; i++) {
        printf("%d. %s (ID: %d) - $%.2f\n",
               (int)(i + 1), result[i].name, result[i].id, result[i].price);
    }

    free(result);
    result = NULL;
    return EXIT_SUCCESS;
}