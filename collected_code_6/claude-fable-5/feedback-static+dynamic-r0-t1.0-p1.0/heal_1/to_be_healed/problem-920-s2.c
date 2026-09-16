#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int is_none;
    int value;
} Element;

typedef struct {
    Element *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static int tuple_is_all_none(const Tuple *t)
{
    size_t i;

    if (t == NULL || t->elements == NULL || t->size == 0U) {
        return 1;
    }
    for (i = 0U; i < t->size; i++) {
        if (t->elements[i].is_none == 0) {
            return 0;
        }
    }
    return 1;
}

static void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0U;
    }
}

static int remove_all_none_tuples(TupleList *list)
{
    size_t read_idx;
    size_t write_idx;

    if (list == NULL || list->tuples == NULL) {
        return -1;
    }

    write_idx = 0U;
    for (read_idx = 0U; read_idx < list->count; read_idx++) {
        if (tuple_is_all_none(&list->tuples[read_idx]) != 0) {
            free_tuple(&list->tuples[read_idx]);
        } else {
            if (write_idx != read_idx) {
                list->tuples[write_idx] = list->tuples[read_idx];
                list->tuples[read_idx].elements = NULL;
                list->tuples[read_idx].size = 0U;
            }
            write_idx++;
        }
    }
    list->count = write_idx;
    return 0;
}

static int make_tuple(Tuple *t, const int *values, const int *none_flags, size_t n)
{
    size_t i;

    if (t == NULL || values == NULL || none_flags == NULL || n == 0U) {
        return -1;
    }
    t->elements = (Element *)malloc(n * sizeof(Element));
    if (t->elements == NULL) {
        t->size = 0U;
        return -1;
    }
    for (i = 0U; i < n; i++) {
        t->elements[i].value = values[i];
        t->elements[i].is_none = none_flags[i];
    }
    t->size = n;
    return 0;
}

static void free_tuple_list(TupleList *list)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (list != NULL) {
        if (list->tuples != NULL) {
            for (i = 0U; i < list->count; i++) {
                free_tuple(&list->tuples[i]);
            }
            free(list->tuples);
            list->tuples = NULL;
        }
        list->count = 0U;
    }
}

static void print_tuple_list(const TupleList *list)
{
    size_t i;
    size_t j;

    if (list == NULL || list->tuples == NULL) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (i = 0U; i < list->count; i++) {
        printf("(");
        for (j = 0U; j < list->tuples[i].size; j++) {
            if (list->tuples[i].elements[j].is_none != 0) {
                printf("None");
            } else {
                printf("%d", list->tuples[i].elements[j].value);
            }
            if (j + 1U < list->tuples[i].size) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1U < list->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    TupleList list;
    /* Possible weaknesses found:
     *  Variable 'v1' can be declared as const array [constVariable]
     */
    int v1[] = {0, 0};
    /* Possible weaknesses found:
     *  Variable 'n1' can be declared as const array [constVariable]
     */
    int n1[] = {1, 1};
    /* Possible weaknesses found:
     *  Variable 'v2' can be declared as const array [constVariable]
     */
    int v2[] = {1, 2};
    /* Possible weaknesses found:
     *  Variable 'n2' can be declared as const array [constVariable]
     */
    int n2[] = {0, 0};
    /* Possible weaknesses found:
     *  Variable 'v3' can be declared as const array [constVariable]
     */
    int v3[] = {0, 3};
    /* Possible weaknesses found:
     *  Variable 'n3' can be declared as const array [constVariable]
     */
    int n3[] = {1, 0};
    /* Possible weaknesses found:
     *  Variable 'v4' can be declared as const array [constVariable]
     */
    int v4[] = {0, 0, 0};
    /* Possible weaknesses found:
     *  Variable 'n4' can be declared as const array [constVariable]
     */
    int n4[] = {1, 1, 1};

    list.count = 4U;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    if (list.tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    memset(list.tuples, 0, list.count * sizeof(Tuple));

    if (make_tuple(&list.tuples[0], v1, n1, 2U) != 0 ||
        make_tuple(&list.tuples[1], v2, n2, 2U) != 0 ||
        make_tuple(&list.tuples[2], v3, n3, 2U) != 0 ||
        make_tuple(&list.tuples[3], v4, n4, 3U) != 0) {
        fprintf(stderr, "Failed to build tuple list\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Original: ");
    print_tuple_list(&list);

    if (remove_all_none_tuples(&list) != 0) {
        fprintf(stderr, "Failed to filter tuple list\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Filtered: ");
    print_tuple_list(&list);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}