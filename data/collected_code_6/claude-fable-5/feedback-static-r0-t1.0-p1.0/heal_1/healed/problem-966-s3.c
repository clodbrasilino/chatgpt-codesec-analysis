#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static int tuple_init(Tuple *t, const int *values, size_t count)
{
    if (t == NULL) {
        return -1;
    }
    t->elements = NULL;
    t->count = 0;
    if (count == 0 || values == NULL) {
        return 0;
    }
    if (count > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    t->elements = malloc(count * sizeof(int));
    if (t->elements == NULL) {
        return -1;
    }
    memcpy(t->elements, values, count * sizeof(int));
    t->count = count;
    return 0;
}

static void tuple_free(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->count = 0;
    }
}

static void tuple_list_free(TupleList *list)
{
    size_t i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        tuple_free(&list->tuples[i]);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

static int remove_empty_tuples(TupleList *list)
{
    size_t i;
    size_t write_index = 0;
    Tuple *shrunk;

    if (list == NULL) {
        return -1;
    }
    for (i = 0; i < list->count; i++) {
        if (list->tuples[i].count > 0) {
            list->tuples[write_index] = list->tuples[i];
            write_index++;
        } else {
            tuple_free(&list->tuples[i]);
        }
    }
    list->count = write_index;
    if (write_index == 0) {
        free(list->tuples);
        list->tuples = NULL;
        return 0;
    }
    shrunk = realloc(list->tuples, write_index * sizeof(Tuple));
    if (shrunk != NULL) {
        list->tuples = shrunk;
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
    printf("[");
    for (i = 0; i < list->count; i++) {
        printf("(");
        for (j = 0; j < list->tuples[i].count; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j + 1 < list->tuples[i].count) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1 < list->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    TupleList list;
    const int a[] = {1, 2};
    const int b[] = {3, 4, 5};
    const int c[] = {6};
    size_t i;

    list.count = 5;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < list.count; i++) {
        list.tuples[i].elements = NULL;
        list.tuples[i].count = 0;
    }

    if (tuple_init(&list.tuples[0], a, 2) != 0 ||
        tuple_init(&list.tuples[1], NULL, 0) != 0 ||
        tuple_init(&list.tuples[2], b, 3) != 0 ||
        tuple_init(&list.tuples[3], NULL, 0) != 0 ||
        tuple_init(&list.tuples[4], c, 1) != 0) {
        fprintf(stderr, "Tuple initialization failed\n");
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    print_tuple_list(&list);

    if (remove_empty_tuples(&list) != 0) {
        fprintf(stderr, "Failed to remove empty tuples\n");
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    printf("After:  ");
    print_tuple_list(&list);

    tuple_list_free(&list);
    return EXIT_SUCCESS;
}