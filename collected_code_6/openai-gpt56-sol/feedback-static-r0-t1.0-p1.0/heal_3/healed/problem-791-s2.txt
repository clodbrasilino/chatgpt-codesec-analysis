#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VALUE_INTEGER,
    VALUE_STRING,
    VALUE_TUPLE
} ValueType;

typedef struct Tuple Tuple;

typedef struct {
    ValueType type;
    union {
        int integer;
        char *string;
        Tuple *tuple;
    } data;
} Value;

struct Tuple {
    size_t size;
    Value *values;
};

static void tuple_destroy(Tuple *tuple);

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static Tuple *tuple_create(size_t size)
{
    Tuple *tuple;

    if (size > SIZE_MAX / sizeof(Value)) {
        return NULL;
    }

    tuple = calloc(1U, sizeof(*tuple));
    if (tuple == NULL) {
        return NULL;
    }

    if (size != 0U) {
        tuple->values = calloc(size, sizeof(*tuple->values));
        if (tuple->values == NULL) {
            free(tuple);
            return NULL;
        }
    }

    tuple->size = size;
    return tuple;
}

static void value_destroy(Value *value)
{
    if (value == NULL) {
        return;
    }

    switch (value->type) {
    case VALUE_STRING:
        free(value->data.string);
        break;
    case VALUE_TUPLE:
        tuple_destroy(value->data.tuple);
        break;
    case VALUE_INTEGER:
        break;
    default:
        break;
    }

    value->type = VALUE_INTEGER;
    value->data.integer = 0;
}

static void tuple_destroy(Tuple *tuple)
{
    size_t index;

    if (tuple == NULL) {
        return;
    }

    for (index = 0U; index < tuple->size; ++index) {
        value_destroy(&tuple->values[index]);
    }

    free(tuple->values);
    free(tuple);
}

static int value_set_string(Value *value, const char *text, size_t text_size)
{
    char *copy;

    if (value == NULL) {
        return -1;
    }

    copy = duplicate_string(text, text_size);
    if (copy == NULL) {
        return -1;
    }

    value_destroy(value);
    value->type = VALUE_STRING;
    value->data.string = copy;

    return 0;
}

static void value_set_integer(Value *value, int number)
{
    if (value == NULL) {
        return;
    }

    value_destroy(value);
    value->type = VALUE_INTEGER;
    value->data.integer = number;
}

static int value_set_tuple(Value *value, Tuple *nested)
{
    if (value == NULL || nested == NULL) {
        return -1;
    }

    value_destroy(value);
    value->type = VALUE_TUPLE;
    value->data.tuple = nested;

    return 0;
}

static int tuple_remove_nested_record(Tuple *tuple, size_t index)
{
    size_t move_count;
    Value *resized;

    if (tuple == NULL || index >= tuple->size ||
        tuple->values == NULL ||
        tuple->values[index].type != VALUE_TUPLE) {
        return -1;
    }

    value_destroy(&tuple->values[index]);

    move_count = tuple->size - index - 1U;
    if (move_count != 0U) {
        memmove(&tuple->values[index],
                &tuple->values[index + 1U],
                move_count * sizeof(*tuple->values));
    }

    --tuple->size;

    if (tuple->size == 0U) {
        free(tuple->values);
        tuple->values = NULL;
        return 0;
    }

    memset(&tuple->values[tuple->size], 0, sizeof(*tuple->values));

    resized = realloc(tuple->values,
                      tuple->size * sizeof(*tuple->values));
    if (resized != NULL) {
        tuple->values = resized;
    }

    return 0;
}

static int tuple_print(const Tuple *tuple)
{
    size_t index;

    if (tuple == NULL || (tuple->size != 0U && tuple->values == NULL)) {
        return -1;
    }

    if (putchar('(') == EOF) {
        return -1;
    }

    for (index = 0U; index < tuple->size; ++index) {
        const Value *value = &tuple->values[index];

        if (index != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        switch (value->type) {
        case VALUE_INTEGER:
            if (printf("%d", value->data.integer) < 0) {
                return -1;
            }
            break;
        case VALUE_STRING:
            if (value->data.string == NULL ||
                printf("\"%s\"", value->data.string) < 0) {
                return -1;
            }
            break;
        case VALUE_TUPLE:
            if (value->data.tuple == NULL ||
                tuple_print(value->data.tuple) != 0) {
                return -1;
            }
            break;
        default:
            return -1;
        }
    }

    return putchar(')') == EOF ? -1 : 0;
}

int main(void)
{
    static const char nested_text[] = "nested";
    static const char remaining_text[] = "remaining";
    Tuple *outer = NULL;
    Tuple *nested = NULL;
    int status = EXIT_FAILURE;

    outer = tuple_create(3U);
    nested = tuple_create(2U);
    if (outer == NULL || nested == NULL) {
        goto cleanup;
    }

    value_set_integer(&outer->values[0], 10);

    if (value_set_string(&nested->values[0], nested_text,
                         sizeof(nested_text)) != 0) {
        goto cleanup;
    }

    value_set_integer(&nested->values[1], 20);

    if (value_set_tuple(&outer->values[1], nested) != 0) {
        goto cleanup;
    }
    nested = NULL;

    if (value_set_string(&outer->values[2], remaining_text,
                         sizeof(remaining_text)) != 0) {
        goto cleanup;
    }

    if (tuple_remove_nested_record(outer, 1U) != 0) {
        goto cleanup;
    }

    if (tuple_print(outer) != 0 || putchar('\n') == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    tuple_destroy(nested);
    tuple_destroy(outer);
    return status;
}