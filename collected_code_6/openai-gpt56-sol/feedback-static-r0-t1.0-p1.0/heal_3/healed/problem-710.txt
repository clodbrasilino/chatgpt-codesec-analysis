#include <stdint.h>
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
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0U; i < tuple->count; ++i) {
            free(tuple->items[i].data);
            tuple->items[i].data = NULL;
            tuple->items[i].size = 0U;
        }

        free(tuple->items);
    }

    tuple->items = NULL;
    tuple->count = 0U;
}

int tuple_set_string(TupleItem *item, const char *source, size_t source_size)
{
    if (item == NULL || source == NULL || source_size == 0U) {
        return -1;
    }

    const char *terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return -1;
    }

    size_t length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return -1;
    }

    size_t allocation_size = length + 1U;
    char *copy = malloc(allocation_size);
    if (copy == NULL) {
        return -1;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    free(item->data);
    item->data = copy;
    item->size = allocation_size;

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
        { value0, sizeof(value0) },
        { value1, sizeof(value1) },
        { value2, sizeof(value2) }
    };

    size_t count = sizeof(values) / sizeof(values[0]);
    Tuple tuple = { NULL, 0U };
    const TupleItem *first = NULL;
    const TupleItem *last = NULL;
    int result = EXIT_FAILURE;

    if (count == 0U || count > SIZE_MAX / sizeof(*tuple.items)) {
        return EXIT_FAILURE;
    }

    tuple.items = calloc(count, sizeof(*tuple.items));
    if (tuple.items == NULL) {
        return EXIT_FAILURE;
    }

    tuple.count = count;

    for (size_t i = 0U; i < count; ++i) {
        if (tuple_set_string(&tuple.items[i],
                             values[i].data,
                             values[i].size) != 0) {
            goto cleanup;
        }
    }

    if (tuple_get_bounds(&tuple, &first, &last) != 0) {
        goto cleanup;
    }

    if (first->data == NULL || first->size == 0U ||
        last->data == NULL || last->size == 0U) {
        goto cleanup;
    }

    if (printf("Initial: %s\nLast: %s\n",
               (const char *)first->data,
               (const char *)last->data) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    tuple_destroy(&tuple);
    return result;
}