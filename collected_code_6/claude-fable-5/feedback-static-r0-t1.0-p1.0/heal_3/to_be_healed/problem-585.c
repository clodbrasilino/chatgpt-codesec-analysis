#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ITEM_NAME_MAX 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[ITEM_NAME_MAX];
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MinHeap;

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

static void heap_swap(Item *a, Item *b)
{
    Item tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_sift_up(MinHeap *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap->data[index].price < heap->data[parent].price) {
            heap_swap(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

static void heap_sift_down(MinHeap *heap, size_t index)
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
        heap_swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
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

static int heap_replace_min(MinHeap *heap, const Item *item)
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
    const Item *ia = a;
    const Item *ib = b;

    if (ia->price < ib->price) {
        return 1;
    }
    if (ia->price > ib->price) {
        return -1;
    }
    return 0;
}

static Item *find_n_expensive(const Item *items, size_t count, size_t n,
                              size_t *result_count)
{
    MinHeap *heap;
    Item *result;
    size_t i;

    if (items == NULL || result_count == NULL || n == 0 || count == 0) {
        return NULL;
    }

    if (n > count) {
        n = count;
    }

    heap = heap_create(n);
    if (heap == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (heap->size < heap->capacity) {
            if (heap_push(heap, &items[i]) != 0) {
                heap_destroy(heap);
                return NULL;
            }
        } else if (items[i].price > heap->data[0].price) {
            if (heap_replace_min(heap, &items[i]) != 0) {
                heap_destroy(heap);
                return NULL;
            }
        }
    }

    if (heap->size == 0 || heap->size > SIZE_MAX / sizeof(Item)) {
        heap_destroy(heap);
        return NULL;
    }

    result = malloc(heap->size * sizeof(Item));
    if (result == NULL) {
        heap_destroy(heap);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, heap->data, heap->size * sizeof(Item));
    *result_count = heap->size;
    heap_destroy(heap);

    qsort(result, *result_count, sizeof(Item), compare_price_desc);
    return result;
}

static void item_init(Item *item, const char *name, double price)
{
    if (item == NULL) {
        return;
    }

    memset(item->name, 0, sizeof(item->name));
    if (name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(name);

        if (len >= sizeof(item->name)) {
            len = sizeof(item->name) - 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(item->name, name, len);
        item->name[len] = '\0';
    }
    item->price = price;
}

int main(void)
{
    Item dataset[10];
    size_t count;
    size_t n = 3;
    size_t result_count = 0;
    Item *result;
    size_t i;

    item_init(&dataset[0], "Laptop", 1200.50);
    item_init(&dataset[1], "Phone", 899.99);
    item_init(&dataset[2], "Headphones", 199.99);
    item_init(&dataset[3], "Monitor", 349.49);
    item_init(&dataset[4], "Keyboard", 89.99);
    item_init(&dataset[5], "Mouse", 49.99);
    item_init(&dataset[6], "Tablet", 649.00);
    item_init(&dataset[7], "Camera", 999.95);
    item_init(&dataset[8], "Printer", 249.00);
    item_init(&dataset[9], "Speaker", 159.99);

    count = sizeof(dataset) / sizeof(dataset[0]);

    result = find_n_expensive(dataset, count, n, &result_count);
    if (result == NULL) {
        fprintf(stderr, "Failed to find the most expensive items\n");
        return EXIT_FAILURE;
    }

    printf("Top %zu most expensive items:\n", result_count);
    for (i = 0; i < result_count; i++) {
        printf("%.*s: %.2f\n", (int)(sizeof(result[i].name) - 1),
               result[i].name, result[i].price);
    }

    free(result);
    return EXIT_SUCCESS;
}