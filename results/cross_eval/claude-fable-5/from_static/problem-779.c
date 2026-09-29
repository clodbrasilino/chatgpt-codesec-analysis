#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const int *items;
    size_t length;
} IntList;

static bool lists_equal(const IntList *a, const IntList *b)
{
    size_t i;

    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->length != b->length) {
        return false;
    }
    for (i = 0; i < a->length; i++) {
        if (a->items[i] != b->items[i]) {
            return false;
        }
    }
    return true;
}

static int count_unique_lists(const IntList *lists, size_t count, size_t *result)
{
    size_t unique = 0;
    size_t i;

    if (result == NULL) {
        return -1;
    }
    if (lists == NULL && count > 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        bool seen = false;
        size_t j;

        if (lists[i].items == NULL && lists[i].length > 0) {
            return -1;
        }
        for (j = 0; j < i; j++) {
            if (lists_equal(&lists[i], &lists[j])) {
                seen = true;
                break;
            }
        }
        if (!seen) {
            unique++;
        }
    }

    *result = unique;
    return 0;
}

int main(void)
{
    static const int a[] = {1, 2, 3};
    static const int b[] = {4, 5};
    static const int c[] = {1, 2, 3};
    static const int d[] = {1, 2};
    static const int e[] = {4, 5};

    IntList lists[5];
    size_t unique_count = 0;

    lists[0].items = a;
    lists[0].length = sizeof(a) / sizeof(a[0]);
    lists[1].items = b;
    lists[1].length = sizeof(b) / sizeof(b[0]);
    lists[2].items = c;
    lists[2].length = sizeof(c) / sizeof(c[0]);
    lists[3].items = d;
    lists[3].length = sizeof(d) / sizeof(d[0]);
    lists[4].items = e;
    lists[4].length = sizeof(e) / sizeof(e[0]);

    if (count_unique_lists(lists, 5, &unique_count) != 0) {
        fprintf(stderr, "Error: failed to count unique lists\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of unique lists: %zu\n", unique_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}