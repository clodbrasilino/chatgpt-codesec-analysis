#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
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
    if (tuple == NULL) {
        return false;
    }

    tuple->values = NULL;
    tuple->length = 0;

    if (length > SIZE_MAX / sizeof(*tuple->values)) {
        return false;
    }

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

static void tuple_destroy(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->values);
    tuple->values = NULL;
    tuple->length = 0;
}

static void tuple_list_destroy(TupleList *list)
{
    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (size_t index = 0; index < list->length; ++index) {
            tuple_destroy(&list->items[index]);
        }
    }

    free(list->items);
    list->items = NULL;
    list->length = 0;
}

static TupleListResult tuple_list_validate(const TupleList *list)
{
    if (list == NULL || (list->length != 0 && list->items == NULL)) {
        return TUPLE_LIST_INVALID_ARGUMENT;
    }

    for (size_t tuple_index = 0;
         tuple_index < list->length;
         ++tuple_index) {
        const Tuple *tuple = &list->items[tuple_index];

        if (tuple->length != 0 && tuple->values == NULL) {
            return TUPLE_LIST_INVALID_ARGUMENT;
        }

        for (size_t value_index = 0;
             value_index < tuple->length;
             ++value_index) {
            TupleValueKind kind = tuple->values[value_index].kind;

            if (kind != TUPLE_VALUE_NONE &&
                kind != TUPLE_VALUE_INTEGER) {
                return TUPLE_LIST_INVALID_VALUE;
            }
        }
    }

    return TUPLE_LIST_SUCCESS;
}

static bool tuple_is_all_none(const Tuple *tuple)
{
    for (size_t index = 0; index < tuple->length; ++index) {
        if (tuple->values[index].kind != TUPLE_VALUE_NONE) {
            return false;
        }
    }

    return true;
}

static TupleListResult remove_all_none_tuples(TupleList *list)
{
    TupleListResult result = tuple_list_validate(list);
    size_t write_index = 0;

    if (result != TUPLE_LIST_SUCCESS) {
        return result;
    }

    for (size_t read_index = 0;
         read_index < list->length;
         ++read_index) {
        Tuple *tuple = &list->items[read_index];

        if (tuple_is_all_none(tuple)) {
            tuple_destroy(tuple);
            continue;
        }

        if (write_index != read_index) {
            list->items[write_index] = *tuple;
            tuple->values = NULL;
            tuple->length = 0;
        }

        ++write_index;
    }

    list->length = write_index;
    return TUPLE_LIST_SUCCESS;
}

static bool write_text(const char *text)
{
    return text != NULL && fputs(text, stdout) != EOF;
}

static bool write_int64(int64_t value)
{
    return fprintf(stdout, "%" PRId64, value) >= 0;
}

static bool print_tuple_list(const TupleList *list)
{
    if (tuple_list_validate(list) != TUPLE_LIST_SUCCESS) {
        return false;
    }

    for (size_t tuple_index = 0;
         tuple_index < list->length;
         ++tuple_index) {
        const Tuple *tuple = &list->items[tuple_index];

        if (putchar('(') == EOF) {
            return false;
        }

        for (size_t value_index = 0;
             value_index < tuple->length;
             ++value_index) {
            const TupleValue *value = &tuple->values[value_index];

            if (value_index != 0 && !write_text(", ")) {
                return false;
            }

            if (value->kind == TUPLE_VALUE_NONE) {
                if (!write_text("None")) {
                    return false;
                }
            } else if (!write_int64(value->integer)) {
                return false;
            }
        }

        if (!write_text(")\n")) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const size_t tuple_count = 4;
    const size_t tuple_length = 3;
    TupleList list = {NULL, 0};
    int exit_status = EXIT_FAILURE;

    if (tuple_count > SIZE_MAX / sizeof(*list.items)) {
        return EXIT_FAILURE;
    }

    list.items = calloc(tuple_count, sizeof(*list.items));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    list.length = tuple_count;

    for (size_t index = 0; index < tuple_count; ++index) {
        if (!tuple_init(&list.items[index], tuple_length)) {
            goto cleanup;
        }
    }

    list.items[1].values[1].kind = TUPLE_VALUE_INTEGER;
    list.items[1].values[1].integer = INT64_C(42);

    list.items[3].values[0].kind = TUPLE_VALUE_INTEGER;
    list.items[3].values[0].integer = INT64_C(7);
    list.items[3].values[2].kind = TUPLE_VALUE_INTEGER;
    list.items[3].values[2].integer = INT64_C(8);

    if (remove_all_none_tuples(&list) != TUPLE_LIST_SUCCESS) {
        goto cleanup;
    }

    if (!print_tuple_list(&list)) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    tuple_list_destroy(&list);
    return exit_status;
}