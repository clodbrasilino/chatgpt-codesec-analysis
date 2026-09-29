#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TUPLE_VALUE_NONE,
    TUPLE_VALUE_INTEGER
} TupleValueKind;

typedef struct {
    TupleValueKind kind;
    int64_t integer;
} TupleValue;

typedef struct {
    TupleValue *values;
    size_t length;
} Tuple;

typedef struct {
    Tuple *items;
    size_t length;
} TupleList;

typedef enum {
    TUPLE_LIST_SUCCESS,
    TUPLE_LIST_INVALID_ARGUMENT,
    TUPLE_LIST_INVALID_VALUE
} TupleListResult;

static bool tuple_init(Tuple *tuple, size_t length)
{
    if (tuple == NULL || length > SIZE_MAX / sizeof(*tuple->values)) {
        return false;
    }

    tuple->values = NULL;
    tuple->length = 0;

    if (length == 0) {
        return true;
    }

    tuple->values = calloc(length, sizeof(*tuple->values));
    if (tuple->values == NULL) {
        return false;
    }

    tuple->length = length;
    return true;
}

static void tuple_list_destroy(TupleList *list)
{
    size_t index;

    if (list == NULL) {
        return;
    }

    for (index = 0; index < list->length; ++index) {
        free(list->items[index].values);
        list->items[index].values = NULL;
        list->items[index].length = 0;
    }

    free(list->items);
    list->items = NULL;
    list->length = 0;
}

static bool tuple_is_all_none(const Tuple *tuple)
{
    size_t index;

    for (index = 0; index < tuple->length; ++index) {
        if (tuple->values[index].kind != TUPLE_VALUE_NONE) {
            return false;
        }
    }

    return true;
}

static TupleListResult remove_all_none_tuples(TupleList *list)
{
    size_t read_index;
    size_t write_index;

    if (list == NULL || (list->length != 0 && list->items == NULL)) {
        return TUPLE_LIST_INVALID_ARGUMENT;
    }

    for (read_index = 0; read_index < list->length; ++read_index) {
        size_t value_index;
        Tuple *tuple = &list->items[read_index];

        if (tuple->length != 0 && tuple->values == NULL) {
            return TUPLE_LIST_INVALID_ARGUMENT;
        }

        for (value_index = 0; value_index < tuple->length; ++value_index) {
            if (tuple->values[value_index].kind != TUPLE_VALUE_NONE &&
                tuple->values[value_index].kind != TUPLE_VALUE_INTEGER) {
                return TUPLE_LIST_INVALID_VALUE;
            }
        }
    }

    write_index = 0;

    for (read_index = 0; read_index < list->length; ++read_index) {
        if (tuple_is_all_none(&list->items[read_index])) {
            free(list->items[read_index].values);
            list->items[read_index].values = NULL;
            list->items[read_index].length = 0;
            continue;
        }

        if (write_index != read_index) {
            list->items[write_index] = list->items[read_index];
            list->items[read_index].values = NULL;
            list->items[read_index].length = 0;
        }

        ++write_index;
    }

    list->length = write_index;
    return TUPLE_LIST_SUCCESS;
}

static void print_tuple_list(const TupleList *list)
{
    size_t tuple_index;

    for (tuple_index = 0; tuple_index < list->length; ++tuple_index) {
        size_t value_index;
        const Tuple *tuple = &list->items[tuple_index];

        putchar('(');

        for (value_index = 0; value_index < tuple->length; ++value_index) {
            if (value_index != 0) {
                fputs(", ", stdout);
            }

            if (tuple->values[value_index].kind == TUPLE_VALUE_NONE) {
                fputs("None", stdout);
            } else {
                printf("%" PRId64, tuple->values[value_index].integer);
            }
        }

        puts(")");
    }
}

int main(void)
{
    TupleList list = {NULL, 0};
    TupleListResult result;
    size_t index;
    const size_t tuple_count = 4;
    const size_t tuple_length = 3;

    if (tuple_count > SIZE_MAX / sizeof(*list.items)) {
        return EXIT_FAILURE;
    }

    list.items = calloc(tuple_count, sizeof(*list.items));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    list.length = tuple_count;

    for (index = 0; index < tuple_count; ++index) {
        if (!tuple_init(&list.items[index], tuple_length)) {
            tuple_list_destroy(&list);
            return EXIT_FAILURE;
        }
    }

    list.items[1].values[1].kind = TUPLE_VALUE_INTEGER;
    list.items[1].values[1].integer = 42;
    list.items[3].values[0].kind = TUPLE_VALUE_INTEGER;
    list.items[3].values[0].integer = 7;
    list.items[3].values[2].kind = TUPLE_VALUE_INTEGER;
    list.items[3].values[2].integer = 8;

    result = remove_all_none_tuples(&list);
    if (result != TUPLE_LIST_SUCCESS) {
        tuple_list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_tuple_list(&list);
    tuple_list_destroy(&list);

    return EXIT_SUCCESS;
}