#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} List;

static int lists_equal(const List *a, const List *b)
{
    size_t i;

    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->length != b->length) {
        return 0;
    }
    for (i = 0; i < a->length; i++) {
        if (a->items[i] != b->items[i]) {
            return 0;
        }
    }
    return 1;
}

int count_unique_lists(const List *lists, size_t count, size_t *result)
{
    size_t i;
    size_t j;
    size_t unique;

    if (result == NULL) {
        return -1;
    }
    if (lists == NULL && count > 0) {
        return -1;
    }

    unique = 0;
    for (i = 0; i < count; i++) {
        int seen = 0;
        for (j = 0; j < i; j++) {
            if (lists_equal(&lists[i], &lists[j])) {
                seen = 1;
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

static int make_list(List *list, const int *values, size_t length)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    list->items = NULL;
    list->length = 0;

    if (length == 0) {
        return 0;
    }

    if (values == NULL) {
        return -1;
    }

    list->items = malloc(length * sizeof(int));
    if (list->items == NULL) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        list->items[i] = values[i];
    }
    list->length = length;
    return 0;
}

static void free_lists(List *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(lists[i].items);
        lists[i].items = NULL;
        lists[i].length = 0;
    }
}

int main(void)
{
    List lists[5];
    size_t created = 0;
    size_t unique = 0;
    const int a[] = {1, 2, 3};
    const int b[] = {4, 5};
    const int c[] = {1, 2, 3};
    const int d[] = {6};
    const int e[] = {4, 5};

    if (make_list(&lists[0], a, sizeof(a) / sizeof(a[0])) != 0) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }
    created = 1;

    if (make_list(&lists[1], b, sizeof(b) / sizeof(b[0])) != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_lists(lists, created);
        return EXIT_FAILURE;
    }
    created = 2;

    if (make_list(&lists[2], c, sizeof(c) / sizeof(c[0])) != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_lists(lists, created);
        return EXIT_FAILURE;
    }
    created = 3;

    if (make_list(&lists[3], d, sizeof(d) / sizeof(d[0])) != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_lists(lists, created);
        return EXIT_FAILURE;
    }
    created = 4;

    if (make_list(&lists[4], e, sizeof(e) / sizeof(e[0])) != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_lists(lists, created);
        return EXIT_FAILURE;
    }
    created = 5;

    if (count_unique_lists(lists, created, &unique) != 0) {
        fprintf(stderr, "Failed to count unique lists\n");
        free_lists(lists, created);
        return EXIT_FAILURE;
    }

    if (printf("Number of unique lists: %zu\n", unique) < 0) {
        free_lists(lists, created);
        return EXIT_FAILURE;
    }

    free_lists(lists, created);
    return EXIT_SUCCESS;
}