#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    char name[64];
    double price;
} Item;

static void min_heapify(Item heap[], size_t size, size_t index) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < size && heap[left].price < heap[smallest].price) {
        smallest = left;
    }
    if (right < size && heap[right].price < heap[smallest].price) {
        smallest = right;
    }
    if (smallest != index) {
        Item temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        min_heapify(heap, size, smallest);
    }
}

static int compare_desc(const void *a, const void *b) {
    const Item *first = (const Item *)a;
    const Item *second = (const Item *)b;

    if (first->price < second->price) {
        return 1;
    }
    if (first->price > second->price) {
        return -1;
    }
    return 0;
}

size_t find_most_expensive(const Item items[], size_t item_count, size_t n, Item result[]) {
    size_t i;

    if (n == 0 || items == NULL || result == NULL || item_count == 0) {
        return 0;
    }

    if (n > item_count) {
        n = item_count;
    }

    for (i = 0; i < n; ++i) {
        result[i] = items[i];
    }

    for (i = n / 2; i > 0; --i) {
        min_heapify(result, n, i - 1);
    }

    for (i = n; i < item_count; ++i) {
        if (items[i].price > result[0].price) {
            result[0] = items[i];
            min_heapify(result, n, 0);
        }
    }

    qsort(result, n, sizeof(Item), compare_desc);
    return n;
}

int main(void) {
    Item items[] = {
        {"apple", 1.25},
        {"banana", 0.85},
        {"cherry", 3.10},
        {"date", 2.40},
        {"elderberry", 4.00},
        {"fig", 2.90}
    };
    size_t item_count = sizeof(items) / sizeof(items[0]);
    size_t n = 3;
    Item top[3];
    size_t found = find_most_expensive(items, item_count, n, top);
    size_t i;

    for (i = 0; i < found; ++i) {
        printf("%s: %.2f\n", top[i].name, top[i].price);
    }

    return 0;
}