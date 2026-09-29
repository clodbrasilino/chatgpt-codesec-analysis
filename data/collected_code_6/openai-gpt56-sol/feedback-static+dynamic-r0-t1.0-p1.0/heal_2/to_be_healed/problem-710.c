#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    void *data;
    size_t size;
} TupleItem;

typedef struct {
    TupleItem *items;
    size_t count;
} Tuple;

int tuple_get_bounds(const Tuple *tuple,
                     const TupleItem **first,
                     const TupleItem **last)
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
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (i = 0U; i < tuple->count; ++i) {
            free(tuple->items[i].data);
            tuple->items[i].data = NULL;
            tuple->items[i].size = 0U;
        }
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0U;
}

int tuple_set_string(TupleItem *item, const char *source, size_t source_size)
{
    size_t length;
    char *copy;

    if (item == NULL || source == NULL || source_size == 0U) {
        return -1;
    }

    length = strnlen(source, source_size);
    if (length == source_size || length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    item->data = copy;
    item->size = length + 1U;
    return 0;
}

int main(void)
{
    static const char value0[] = "initial";
    static const char value1[] = "middle";
    static const char value2[] = "last";
    static const struct {
        const char *data;
        size_t size;
    } values[] = {
        {value0, sizeof(value0)},
        {value1, sizeof(value1)},
        {value2, sizeof(value2)}
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    Tuple tuple = {NULL, 0U};
    const TupleItem *first = NULL;
    const TupleItem *last = NULL;
    size_t i;

    if (count > SIZE_MAX / sizeof(*tuple.items)) {
        return EXIT_FAILURE;
    }

    tuple.items = calloc(count, sizeof(*tuple.items));
    if (tuple.items == NULL) {
        return EXIT_FAILURE;
    }
    tuple.count = count;

    for (i = 0U; i < count; ++i) {
        if (tuple_set_string(&tuple.items[i],
                             values[i].data,
                             values[i].size) != 0) {
            tuple_destroy(&tuple);
            return EXIT_FAILURE;
        }
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