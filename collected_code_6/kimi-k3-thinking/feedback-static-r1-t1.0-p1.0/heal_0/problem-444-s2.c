#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

static int init_tuple(Tuple *tuple, const int *values, size_t length)
{
    size_t i;

    if (tuple == NULL || (values == NULL && length > 0)) {
        return -1;
    }
    tuple->data = NULL;
    tuple->length = 0;
    if (length == 0) {
        return 0;
    }
    if (length > SIZE_MAX / sizeof(*tuple->data)) {
        return -1;
    }
    tuple->data = malloc(length * sizeof(*tuple->data));
    if (tuple->data == NULL) {
        return -1;
    }
    for (i = 0; i < length; i++) {
        tuple->data[i] = values[i];
    }
    tuple->length = length;
    return 0;
}

static int trim_tuple(Tuple *tuple, size_t k)
{
    size_t new_length;
    size_t i;
    int *new_data;

    if (tuple == NULL) {
        return -1;
    }
    if (tuple->data == NULL) {
        tuple->length = 0;
        return 0;
    }
    if (k == 0) {
        return 0;
    }
    if (k > tuple->length / 2) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->length = 0;
        return 0;
    }
    new_length = tuple->length - (2 * k);
    if (new_length == 0) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->length = 0;
        return 0;
    }
    if (new_length > SIZE_MAX / sizeof(*new_data)) {
        return -1;
    }
    new_data = malloc(new_length * sizeof(*new_data));
    if (new_data == NULL) {
        return -1;
    }
    for (i = 0; i < new_length; i++) {
        new_data[i] = tuple->data[k + i];
    }
    free(tuple->data);
    tuple->data = new_data;
    tuple->length = new_length;
    return 0;
}

static int trim_tuple_list(TupleList *list, size_t k)
{
    size_t i;

    if (list == NULL || (list->items == NULL && list->count > 0)) {
        return -1;
    }
    for (i = 0; i < list->count; i++) {
        if (trim_tuple(&list->items[i], k) != 0) {
            return -1;
        }
    }
    return 0;
}

static void print_tuple_list(const TupleList *list)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        printf("(");
        for (j = 0; j < list->items[i].length; j++) {
            printf("%d", list->items[i].data[j]);
            if (j + 1 < list->items[i].length) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

static void free_tuple_list(TupleList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        free(list->items[i].data);
        list->items[i].data = NULL;
        list->items[i].length = 0;
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
}

int main(void)
{
    int a[] = {5, 2, 8, 1, 9, 3};
    int b[] = {10, 20, 30, 40};
    int c[] = {7, 14, 21, 28, 35, 42, 49};
    TupleList list;
    size_t k = 1;

    list.items = calloc(3, sizeof(*list.items));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }
    list.count = 3;

    if (init_tuple(&list.items[0], a, sizeof(a) / sizeof(a[0])) != 0 ||
        init_tuple(&list.items[1], b, sizeof(b) / sizeof(b[0])) != 0 ||
        init_tuple(&list.items[2], c, sizeof(c) / sizeof(c[0])) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Original tuple list:\n");
    print_tuple_list(&list);

    if (trim_tuple_list(&list, k) != 0) {
        fprintf(stderr, "Failed to trim tuple list\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Tuple list after trimming by %zu:\n", k);
    print_tuple_list(&list);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}