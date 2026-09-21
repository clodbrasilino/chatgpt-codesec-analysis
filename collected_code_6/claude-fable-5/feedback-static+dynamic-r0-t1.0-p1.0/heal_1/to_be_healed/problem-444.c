#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static int trim_tuple(const Tuple *src, size_t k, Tuple *dest)
{
    size_t new_size;

    if (src == NULL || dest == NULL) {
        return -1;
    }

    if (src->size <= 2U * k) {
        dest->elements = NULL;
        dest->size = 0U;
        return 0;
    }

    new_size = src->size - 2U * k;
    dest->elements = malloc(new_size * sizeof(int));
    if (dest->elements == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest->elements, src->elements + k, new_size * sizeof(int));
    dest->size = new_size;
    return 0;
}

static int trim_tuple_list(const TupleList *src, size_t k, TupleList *dest)
{
    size_t i;
    size_t j;

    if (src == NULL || dest == NULL) {
        return -1;
    }

    dest->tuples = malloc(src->count * sizeof(Tuple));
    if (dest->tuples == NULL) {
        return -1;
    }
    dest->count = src->count;

    for (i = 0U; i < src->count; i++) {
        if (trim_tuple(&src->tuples[i], k, &dest->tuples[i]) != 0) {
            for (j = 0U; j < i; j++) {
                free(dest->tuples[j].elements);
            }
            free(dest->tuples);
            dest->tuples = NULL;
            dest->count = 0U;
            return -1;
        }
    }
    return 0;
}

static void free_tuple_list(TupleList *list)
{
    size_t i;

    if (list == NULL || list->tuples == NULL) {
        return;
    }
    for (i = 0U; i < list->count; i++) {
        free(list->tuples[i].elements);
        list->tuples[i].elements = NULL;
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0U;
}

static void print_tuple_list(const TupleList *list)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }
    printf("[");
    for (i = 0U; i < list->count; i++) {
        printf("(");
        for (j = 0U; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
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
    int data0[] = {5, 3, 2, 1, 4};
    int data1[] = {3, 4, 9, 2, 1};
    int data2[] = {9, 1, 2, 3, 5};
    int data3[] = {4, 8, 2, 1, 7};
    Tuple tuples[4];
    TupleList input;
    TupleList output;
    size_t k = 2U;

    tuples[0].elements = data0;
    tuples[0].size = 5U;
    tuples[1].elements = data1;
    tuples[1].size = 5U;
    tuples[2].elements = data2;
    tuples[2].size = 5U;
    tuples[3].elements = data3;
    tuples[3].size = 5U;

    input.tuples = tuples;
    input.count = 4U;

    output.tuples = NULL;
    output.count = 0U;

    if (trim_tuple_list(&input, k, &output) != 0) {
        fprintf(stderr, "Failed to trim tuple list\n");
        return EXIT_FAILURE;
    }

    printf("Original: ");
    print_tuple_list(&input);
    printf("Trimmed:  ");
    print_tuple_list(&output);

    free_tuple_list(&output);
    return EXIT_SUCCESS;
}