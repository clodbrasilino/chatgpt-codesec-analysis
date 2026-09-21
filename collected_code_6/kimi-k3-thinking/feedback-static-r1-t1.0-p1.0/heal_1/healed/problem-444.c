#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

int init_tuple(Tuple *t, const int *values, size_t size)
{
    size_t alloc_size;

    if (t == NULL) {
        return -1;
    }
    t->data = NULL;
    t->size = 0;
    if (size == 0) {
        return 0;
    }
    if (values == NULL) {
        return -1;
    }
    if (size > SIZE_MAX / sizeof(*t->data)) {
        return -1;
    }
    alloc_size = size * sizeof(*t->data);
    t->data = malloc(alloc_size);
    if (t->data == NULL) {
        return -1;
    }
    if (alloc_size / sizeof(*t->data) != size) {
        free(t->data);
        t->data = NULL;
        return -1;
    }
    memcpy(t->data, values, alloc_size);
    t->size = size;
    return 0;
}

int trim_tuple(Tuple *t, size_t k)
{
    size_t remove_total;
    size_t new_size;
    size_t copy_size;
    int *new_data;

    if (t == NULL) {
        return -1;
    }
    if (t->size == 0 || t->data == NULL) {
        return 0;
    }
    if (k > SIZE_MAX - k) {
        remove_total = t->size;
    } else {
        remove_total = 2 * k;
    }
    if (remove_total >= t->size) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
        return 0;
    }
    new_size = t->size - remove_total;
    if (new_size > SIZE_MAX / sizeof(*new_data)) {
        return -1;
    }
    if (k > t->size || new_size > t->size - k) {
        return -1;
    }
    copy_size = new_size * sizeof(*new_data);
    new_data = malloc(copy_size);
    if (new_data == NULL) {
        return -1;
    }
    if (copy_size / sizeof(*new_data) != new_size) {
        free(new_data);
        return -1;
    }
    memcpy(new_data, t->data + k, copy_size);
    free(t->data);
    t->data = new_data;
    t->size = new_size;
    return 0;
}

int trim_tuple_list(TupleList *list, size_t k)
{
    if (list == NULL || (list->count > 0 && list->items == NULL)) {
        return -1;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (trim_tuple(&list->items[i], k) != 0) {
            return -1;
        }
    }
    return 0;
}

void print_tuple_list(const TupleList *list)
{
    if (list == NULL || (list->count > 0 && list->items == NULL)) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        printf("(");
        for (size_t j = 0; j < list->items[i].size; j++) {
            printf("%d", list->items[i].data[j]);
            if (j + 1 < list->items[i].size) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

void free_tuple_list(TupleList *list)
{
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->items[i].data);
            list->items[i].data = NULL;
            list->items[i].size = 0;
        }
        free(list->items);
        list->items = NULL;
    }
    list->count = 0;
}

int main(void)
{
    const int a[] = {5, 3, 2, 1, 4, 9};
    const int b[] = {7, 8, 2, 6};
    const int c[] = {1, 2, 3};
    const size_t tuple_count = 3;
    const size_t k = 1;
    TupleList list;

    list.items = NULL;
    list.count = 0;

    if (tuple_count > SIZE_MAX / sizeof(*list.items)) {
        return EXIT_FAILURE;
    }
    list.items = malloc(tuple_count * sizeof(*list.items));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < tuple_count; i++) {
        list.items[i].data = NULL;
        list.items[i].size = 0;
    }
    list.count = tuple_count;

    if (init_tuple(&list.items[0], a, sizeof(a) / sizeof(a[0])) != 0 ||
        init_tuple(&list.items[1], b, sizeof(b) / sizeof(b[0])) != 0 ||
        init_tuple(&list.items[2], c, sizeof(c) / sizeof(c[0])) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Original tuples:\n");
    print_tuple_list(&list);

    if (trim_tuple_list(&list, k) != 0) {
        fprintf(stderr, "Failed to trim tuple list\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Tuples after trimming by %zu:\n", k);
    print_tuple_list(&list);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}