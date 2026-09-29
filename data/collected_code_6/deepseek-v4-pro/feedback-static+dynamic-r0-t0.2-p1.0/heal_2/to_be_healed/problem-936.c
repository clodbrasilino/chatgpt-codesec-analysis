#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *value;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

typedef struct {
    size_t order_size;
    int order[];
} SortContext;

static int find_index(const int *order, size_t order_size, int id) {
    for (size_t i = 0; i < order_size; ++i) {
        if (order[i] == id) {
            return (int)i;
        }
    }
    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'context' can be declared as pointer to const. However it seems that 'compare_tuples' is a callback function, if 'context' is declared with const you might also need to cast function pointer(s). [constParameterCallback]
 *  Parameter 'context' can be declared as pointer to const
 */
static int compare_tuples(const void *a, const void *b, void *context) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    const SortContext *ctx = (const SortContext *)context;
    const int *order = ctx->order;
    size_t order_size = ctx->order_size;

    int index_a = find_index(order, order_size, tuple_a->id);
    int index_b = find_index(order, order_size, tuple_b->id);

    if (index_a == -1 && index_b == -1) return 0;
    if (index_a == -1) return 1;
    if (index_b == -1) return -1;
    return index_a - index_b;
}

int rearrange_tuples(TupleList *list, const int *order, size_t order_size) {
    if (list == NULL || order == NULL || order_size == 0) {
        return -1;
    }

    if (list->count == 0) {
        return 0;
    }

    SortContext *context = malloc(sizeof(SortContext) + order_size * sizeof(int));
    if (context == NULL) {
        return -1;
    }

    context->order_size = order_size;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(context->order, order, order_size * sizeof(int));

    /* Possible weaknesses found:
     *  passing argument 5 of 'qsort_r' from incompatible pointer type [-Wincompatible-pointer-types]
     *  You might need to cast the function pointer here
     */
    qsort_r(list->tuples, list->count, sizeof(Tuple), compare_tuples, context);

    free(context);
    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {3, "three"},
        {1, "one"},
        {2, "two"},
        {4, "four"}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    int order[] = {2, 1, 3};
    size_t order_size = sizeof(order) / sizeof(order[0]);

    TupleList list = {tuples, tuple_count};

    if (rearrange_tuples(&list, order, order_size) != 0) {
        fprintf(stderr, "Failed to rearrange tuples\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; ++i) {
        printf("(%d, %s)\n", list.tuples[i].id, list.tuples[i].value);
    }

    return EXIT_SUCCESS;
}