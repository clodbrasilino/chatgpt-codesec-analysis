#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    double price;
} Item;

static int item_less(const Item *a, const Item *b)
{
    if (a->price < b->price) {
        return 1;
    }

    if (a->price > b->price) {
        return 0;
    }

    if (a->name == NULL) {
        return b->name != NULL;
    }

    if (b->name == NULL) {
        return 0;
    }

    return strcmp(a->name, b->name) > 0;
}

static void swap_items(Item *a, Item *b)
{
    Item temporary = *a;
    *a = *b;
    *b = temporary;
}

static void sift_up(Item *heap, size_t index)
{
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (!item_less(&heap[index], &heap[parent])) {
            break;
        }

        swap_items(&heap[index], &heap[parent]);
        index = parent;
    }
}

static void sift_down(Item *heap, size_t size, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 1U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        right = left + 1U;

        if (left < size && item_less(&heap[left], &heap[smallest])) {
            smallest = left;
        }

        if (right < size && item_less(&heap[right], &heap[smallest])) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_items(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static int descending_price(const void *left, const void *right)
{
    const Item *a = left;
    const Item *b = right;

    if (a->price < b->price) {
        return 1;
    }

    if (a->price > b->price) {
        return -1;
    }

    if (a->name == NULL && b->name == NULL) {
        return 0;
    }

    if (a->name == NULL) {
        return 1;
    }

    if (b->name == NULL) {
        return -1;
    }

    return strcmp(a->name, b->name);
}

static int find_most_expensive(const Item *items, size_t count, size_t n,
                               Item **result, size_t *result_count)
{
    Item *heap;
    size_t heap_size = 0U;
    size_t i;

    if (result == NULL || result_count == NULL ||
        (items == NULL && count != 0U)) {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;
    *result_count = 0U;

    if (n == 0U || count == 0U) {
        return 0;
    }

    if (n > count) {
        n = count;
    }

    if (n > SIZE_MAX / sizeof(*heap)) {
        errno = EOVERFLOW;
        return -1;
    }

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (heap_size < n) {
            heap[heap_size] = items[i];
            sift_up(heap, heap_size);
            ++heap_size;
        } else if (item_less(&heap[0], &items[i])) {
            heap[0] = items[i];
            sift_down(heap, heap_size, 0U);
        }
    }

    qsort(heap, heap_size, sizeof(*heap), descending_price);

    *result = heap;
    *result_count = heap_size;
    return 0;
}

int main(void)
{
    const Item items[] = {
        {"Laptop", 1299.99},
        {"Phone", 899.50},
        {"Monitor", 449.00},
        {"Keyboard", 129.99},
        {"Tablet", 749.00},
        {"Camera", 1599.95},
        {"Headphones", 299.99}
    };
    const size_t item_count = sizeof(items) / sizeof(items[0]);
    const size_t n = 3U;
    Item *result = NULL;
    size_t result_count = 0U;
    size_t i;

    if (find_most_expensive(items, item_count, n,
                            &result, &result_count) != 0) {
        perror("find_most_expensive");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < result_count; ++i) {
        const char *name = result[i].name != NULL ? result[i].name : "(null)";

        if (printf("%s: %.2f\n", name, result[i].price) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}