#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

int tuple_list_init(TupleList *list, size_t capacity)
{
    if (list == NULL) {
        return -1;
    }
    list->tuples = NULL;
    list->count = 0;
    if (capacity > 0) {
        list->tuples = calloc(capacity, sizeof(Tuple));
        if (list->tuples == NULL) {
            return -1;
        }
    }
    return 0;
}

int tuple_init(Tuple *t, const int *values, size_t count)
{
    if (t == NULL) {
        return -1;
    }
    t->items = NULL;
    t->count = 0;
    if (count > 0) {
        if (values == NULL) {
            return -1;
        }
        t->items = malloc(count * sizeof(int));
        if (t->items == NULL) {
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->items, values, count * sizeof(int));
        t->count = count;
    }
    return 0;
}

void tuple_free(Tuple *t)
{
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
        t->count = 0;
    }
}

void tuple_list_free(TupleList *list)
{
    if (list != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            tuple_free(&list->tuples[i]);
        }
        free(list->tuples);
        list->tuples = NULL;
        list->count = 0;
    }
}

int remove_empty_tuples(TupleList *list)
{
    if (list == NULL || (list->tuples == NULL && list->count > 0)) {
        return -1;
    }
    size_t write_index = 0;
    for (size_t read_index = 0; read_index < list->count; read_index++) {
        if (list->tuples[read_index].count > 0) {
            if (write_index != read_index) {
                list->tuples[write_index] = list->tuples[read_index];
                list->tuples[read_index].items = NULL;
                list->tuples[read_index].count = 0;
            }
            write_index++;
        } else {
            tuple_free(&list->tuples[read_index]);
        }
    }
    list->count = write_index;
    return 0;
}

void print_tuple_list(const TupleList *list)
{
    if (list == NULL) {
        return;
    }
    printf("[");
    for (size_t i = 0; i < list->count; i++) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].count; j++) {
            printf("%d", list->tuples[i].items[j]);
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
    /* Possible weaknesses found:
     *  Variable 'a' can be declared as const array [constVariable]
     */
    int a[] = {1, 2};
    /* Possible weaknesses found:
     *  Variable 'b' can be declared as const array [constVariable]
     */
    int b[] = {3};
    /* Possible weaknesses found:
     *  Variable 'c' can be declared as const array [constVariable]
     */
    int c[] = {4, 5, 6};

    if (tuple_list_init(&list, 5) != 0) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    if (tuple_init(&list.tuples[0], a, 2) != 0 ||
        tuple_init(&list.tuples[1], NULL, 0) != 0 ||
        tuple_init(&list.tuples[2], b, 1) != 0 ||
        tuple_init(&list.tuples[3], NULL, 0) != 0 ||
        tuple_init(&list.tuples[4], c, 3) != 0) {
        fprintf(stderr, "Tuple initialization failure\n");
        list.count = 5;
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }
    list.count = 5;

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