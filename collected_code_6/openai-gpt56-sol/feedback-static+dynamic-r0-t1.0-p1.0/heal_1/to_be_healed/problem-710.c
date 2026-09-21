#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t size;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t count;
} Tuple;

int tuple_get_bounds(const Tuple *tuple, const TupleItem **first, const TupleItem **last)
{
    if (tuple == NULL || first == NULL || last == NULL ||
        tuple->items == NULL || tuple->count == 0U) {
        return -1;
    }

    *first = &tuple->items[0];
    *last = &tuple->items[tuple->count - 1U];
    return 0;
}

void tuple_destroy(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0U; i < tuple->count; ++i) {
        free(tuple->items[i].data);
        tuple->items[i].data = NULL;
        tuple->items[i].size = 0U;
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0U;
}

int main(void)
{
    const char *values[] = {"initial", "middle", "last"};
    const size_t count = sizeof(values) / sizeof(values[0]);
    Tuple tuple = {NULL, 0U};
    const TupleItem *first = NULL;
    const TupleItem *last = NULL;
    size_t i;

    tuple.items = calloc(count, sizeof(*tuple.items));
    if (tuple.items == NULL) {
        return EXIT_FAILURE;
    }
    tuple.count = count;

    for (i = 0U; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(values[i]) + 1U;

        tuple.items[i].data = malloc(length);
        if (tuple.items[i].data == NULL) {
            tuple_destroy(&tuple);
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple.items[i].data, values[i], length);
        tuple.items[i].size = length;
    }

    if (tuple_get_bounds(&tuple, &first, &last) != 0) {
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    if (printf("Initial: %s\nLast: %s\n",
               (const char *)first->data,
               (const char *)last->data) < 0) {
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    tuple_destroy(&tuple);
    return EXIT_SUCCESS;
}