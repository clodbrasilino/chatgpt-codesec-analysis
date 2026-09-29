#include <stdio.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    const Tuple *items;
    size_t count;
} TupleList;

int extract_nth_element(const TupleList *list, size_t n, Tuple *out) {
    if (list == NULL || out == NULL) {
        return -1;
    }
    if (list->items == NULL) {
        return -1;
    }
    if (n >= list->count) {
        return -1;
    }
    *out = list->items[n];
    return 0;
}

int main(void) {
    Tuple items[] = {{10, 20}, {30, 40}, {50, 60}};
    TupleList list = {items, sizeof(items) / sizeof(items[0])};
    Tuple result;

    if (extract_nth_element(&list, 1, &result) == 0) {
        printf("Element at index 1: (%d, %d)\n", result.first, result.second);
    } else {
        printf("Failed to extract element at index 1.\n");
    }

    if (extract_nth_element(&list, 5, &result) == 0) {
        printf("Element at index 5: (%d, %d)\n", result.first, result.second);
    } else {
        printf("Index 5 out of bounds, handled correctly.\n");
    }

    if (extract_nth_element(NULL, 0, &result) == 0) {
        printf("Element extracted from NULL list.\n");
    } else {
        printf("NULL list handled correctly.\n");
    }

    return 0;
}