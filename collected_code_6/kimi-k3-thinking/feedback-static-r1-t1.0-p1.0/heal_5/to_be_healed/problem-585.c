#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME_LENGTH 1024

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

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    /* Possible weaknesses found:
     *  Either the condition 'len<max_len' is redundant or the array 's[1]' is accessed at index 1023, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'len<max_len' is not redundant
     *  Array index out of bounds
     */
    while (len < max_len && s[len] != '\0')
        len++;
    return len;
}

static char *string_duplicate(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL)
        s = "";

    /* Possible weaknesses found:
     *  Calling function 'bounded_strlen', 2nd argument '1024' value is 1024
     */
    len = bounded_strlen(s, MAX_NAME_LENGTH);
    copy = (char *)malloc(len + 1);
    if (copy == NULL)
        return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

static int item_init(Item *item, int id, const char *name, double price)
{
    if (item == NULL)
        return -1;

    item->id = id;
    item->price = price;
    item->name = string_duplicate(name);
    if (item->name == NULL)
        return -1;
    return 0;
}

static int item_copy(Item *dst, const Item *src)
{
    if (dst == NULL || src == NULL)
        return -1;
    return item_init(dst, src->id, src->name, src->price);
}

static void item_release(Item *item)
{
    if (item != NULL) {
        free(item->name);
        item->name = NULL;
    }
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
        size_t i;

        for (i = 0; i < heap->size; i++)
            item_release(&heap->data[i]);
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

    if (item_copy(&heap->data[heap->size], item) != 0)
        return -1;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

static int heap_replace_top(MinHeap *heap, const Item *item)
{
    Item replacement;

    if (heap == NULL || item == NULL || heap->size == 0)
        return -1;

    if (item_copy(&replacement, item) != 0)
        return -1;

    item_release(&heap->data[0]);
    heap->data[0] = replacement;
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

    for (i = 0; i < heap.size; i++) {
        if (item_copy(&result[i], &heap.data[i]) != 0) {
            while (i > 0) {
                i--;
                item_release(&result[i]);
            }
            heap_destroy(&heap);
            return -1;
        }
    }

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
    static const struct {
        int id;
        const char *name;
        double price;
    } dataset_spec[] = {
        {1,  "Laptop",        1299.99},
        {2,  "Mouse",           25.50},
        {3,  "Keyboard",        89.99},
        {4,  "Monitor",        449.00},
        {5,  "Headphones",     199.95},
        {6,  "Webcam",          79.99},
        {7,  "Printer",        329.50},
        {8,  "USB Cable",        9.99},
        {9,  "SSD Drive",      159.00},
        {10, "Graphics Card",  899.00}
    };
    size_t count = sizeof(dataset_spec) / sizeof(dataset_spec[0]);
    size_t n = 3;
    Item *dataset = NULL;
    Item *result = NULL;
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

    if (count > SIZE_MAX / sizeof(*dataset)) {
        fprintf(stderr, "Dataset size is too large\n");
        return EXIT_FAILURE;
    }

    dataset = (Item *)malloc(count * sizeof(*dataset));
    if (dataset == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (item_init(&dataset[i], dataset_spec[i].id, dataset_spec[i].name, dataset_spec[i].price) != 0) {
            while (i > 0) {
                i--;
                item_release(&dataset[i]);
            }
            free(dataset);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    result = (Item *)malloc(n * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        for (i = 0; i < count; i++)
            item_release(&dataset[i]);
        free(dataset);
        return EXIT_FAILURE;
    }

    if (find_n_most_expensive(dataset, count, n, result) != 0) {
        fprintf(stderr, "Failed to find top %zu items\n", n);
        free(result);
        for (i = 0; i < count; i++)
            item_release(&dataset[i]);
        free(dataset);
        return EXIT_FAILURE;
    }

    qsort(result, n, sizeof(*result), compare_items_desc);

    printf("Top %zu most expensive items:\n", n);
    for (i = 0; i < n; i++)
        printf("%d. %-15s $%.2f\n", result[i].id, result[i].name, result[i].price);

    for (i = 0; i < n; i++)
        item_release(&result[i]);
    free(result);
    result = NULL;

    for (i = 0; i < count; i++)
        item_release(&dataset[i]);
    free(dataset);
    dataset = NULL;

    return EXIT_SUCCESS;
}