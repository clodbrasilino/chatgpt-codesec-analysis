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
    if (tuple == NULL) {
        return false;
    }

    tuple->values = NULL;
    tuple->length = 0;

    if (length == 0) {
        return true;
    }

    if (length > SIZE_MAX / sizeof(*tuple->values)) {
        return false;
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

    for (size_t index = 0; index < list->length; ++index) {
        tuple_destroy(&list->items[index]);
    }

    free(list->items);
    list->items = NULL;
    list->length = 0;
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

static TupleListResult validate_tuple_list(const TupleList *list)
{
    if (list == NULL) {
        return TUPLE_LIST_INVALID_ARGUMENT;
    }

    if (list->length != 0 && list->items == NULL) {
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

static TupleListResult remove_all_none_tuples(TupleList *list)
{
    TupleListResult result = validate_tuple_list(list);

    if (result != TUPLE_LIST_SUCCESS) {
        return result;
    }

    size_t write_index = 0;

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

static void print_uint64(uint64_t value)
{
    char digits[20];
    size_t length = 0;

    do {
        digits[length++] = (char)('0' + value % UINT64_C(10));
        value /= UINT64_C(10);
    } while (value != 0);

    while (length != 0) {
        putchar((unsigned char)digits[--length]);
    }
}

static void print_int64(int64_t value)
{
    uint64_t magnitude;

    if (value < 0) {
        putchar('-');
        magnitude = (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)value;
    }

    print_uint64(magnitude);
}

static void print_tuple_list(const TupleList *list)
{
    if (validate_tuple_list(list) != TUPLE_LIST_SUCCESS) {
        return;
    }

    for (size_t tuple_index = 0;
         tuple_index < list->length;
         ++tuple_index) {
        const Tuple *tuple = &list->items[tuple_index];

        putchar('(');

        for (size_t value_index = 0;
             value_index < tuple->length;
             ++value_index) {
            if (value_index != 0) {
                fputs(", ", stdout);
            }

            const TupleValue *value = &tuple->values[value_index];

            if (value->kind == TUPLE_VALUE_NONE) {
                fputs("None", stdout);
            } else {
                print_int64(value->integer);
            }
        }

        puts(")");
    }
}

int main(void)
{
    const size_t tuple_count = 4;
    const size_t tuple_length = 3;
    TupleList list = {NULL, 0};

    if (tuple_count > SIZE_MAX / sizeof(*list.items)) {
        return EXIT_FAILURE;
    }

    list.items = calloc(tuple_count, sizeof(*list.items));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < tuple_count; ++index) {
        if (!tuple_init(&list.items[index], tuple_length)) {
            tuple_list_destroy(&list);
            return EXIT_FAILURE;
        }

        ++list.length;
    }

    list.items[1].values[1].kind = TUPLE_VALUE_INTEGER;
    list.items[1].values[1].integer = INT64_C(42);

    list.items[3].values[0].kind = TUPLE_VALUE_INTEGER;
    list.items[3].values[0].integer = INT64_C(7);

    list.items[3].values[2].kind = TUPLE_VALUE_INTEGER;
    list.items[3].values[2].integer = INT64_C(8);

    TupleListResult result = remove_all_none_tuples(&list);

    if (result != TUPLE_LIST_SUCCESS) {
        tuple_list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_tuple_list(&list);
    tuple_list_destroy(&list);

    return EXIT_SUCCESS;
}