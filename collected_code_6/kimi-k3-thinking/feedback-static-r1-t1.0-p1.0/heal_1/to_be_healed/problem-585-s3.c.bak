#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    double price;
} Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} MinHeap;

static void swap_items(Item *a, Item *b)
{
    Item temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MinHeap *heap, size_t index)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'smallest' can be reduced. [variableScope]
     */
    size_t smallest;
    /* Possible weaknesses found:
     *  The scope of the variable 'left' can be reduced. [variableScope]
     */
    size_t left;
    /* Possible weaknesses found:
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    size_t right;

    for (;;) {
        smallest = index;
        left = 2 * index + 1;
        right = 2 * index + 2;

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
    /* Possible weaknesses found:
     *  The scope of the variable 'parent' can be reduced. [variableScope]
     */
    size_t parent;

    while (index > 0) {
        parent = (index - 1) / 2;
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
    heap->data[heap->size] = *item;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

static int heap_replace_root(MinHeap *heap, const Item *item)
{
    if (heap == NULL || item == NULL || heap->size == 0)
        return -1;
    heap->data[0] = *item;
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

    heap.data = (Item *)malloc(n * sizeof(Item));
    if (heap.data == NULL)
        return 0;
    heap.size = 0;
    heap.capacity = n;

    for (i = 0; i < count; i++) {
        if (heap.size < heap.capacity) {
            if (heap_push(&heap, &items[i]) != 0) {
                free(heap.data);
                heap.data = NULL;
                return 0;
            }
        } else if (items[i].price > heap.data[0].price) {
            heap_replace_root(&heap, &items[i]);
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

int main(void)
{
    Item dataset[] = {
        {1, "Laptop", 1299.99},
        {2, "Smartphone", 899.50},
        {3, "Headphones", 249.99},
        {4, "Monitor", 399.00},
        {5, "Keyboard", 129.99},
        {6, "Mouse", 59.99},
        {7, "Tablet", 549.00},
        {8, "Printer", 199.99},
        {9, "Camera", 749.99},
        {10, "Speaker", 89.99}
    };
    size_t count = sizeof(dataset) / sizeof(dataset[0]);
    /* Possible weaknesses found:
     *  Assignment 'n=3', assigned value is 3
     */
    size_t n = 3;
    size_t alloc_size;
    size_t found;
    size_t i;
    Item *result;

    /* Possible weaknesses found:
     *  Condition 'n<count' is always true [knownConditionTrueFalse]
     *  Condition 'n<count' is always true
     */
    alloc_size = (n < count) ? n : count;
    result = (Item *)malloc(alloc_size * sizeof(Item));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    found = find_n_most_expensive(dataset, count, n, result);
    if (found == 0) {
        fprintf(stderr, "No items found\n");
        free(result);
        result = NULL;
        return EXIT_FAILURE;
    }

    printf("Top %zu most expensive items:\n", found);
    for (i = 0; i < found; i++) {
        printf("%zu. %s (ID: %d) - $%.2f\n",
               i + 1, result[i].name, result[i].id, result[i].price);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}