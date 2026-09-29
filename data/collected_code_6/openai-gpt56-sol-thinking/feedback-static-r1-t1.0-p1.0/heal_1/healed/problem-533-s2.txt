#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VALUE_INT,
    VALUE_DOUBLE,
    VALUE_CHAR,
    VALUE_STRING
} ValueType;

typedef struct {
    char *data;
    size_t length;
} StringValue;

typedef struct {
    ValueType type;
    union {
        int integer;
        double real;
        char character;
        StringValue string;
    } data;
} Element;

typedef struct {
    Element *elements;
    size_t length;
    size_t capacity;
} Tuple;

static void tuple_init(Tuple *tuple)
{
    if (tuple != NULL) {
        tuple->elements = NULL;
        tuple->length = 0;
        tuple->capacity = 0;
    }
}

static bool value_type_is_valid(ValueType type)
{
    return type >= VALUE_INT && type <= VALUE_STRING;
}

static bool duplicate_string(const char *source, size_t length, char **result)
{
    char *copy;
    size_t index;

    if (result == NULL) {
        return false;
    }

    *result = NULL;

    if (source == NULL || length == SIZE_MAX) {
        return false;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return false;
    }

    for (index = 0; index < length; index++) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    *result = copy;
    return true;
}

static bool tuple_reserve(Tuple *tuple, size_t required)
{
    size_t maximum_capacity;
    size_t new_capacity;
    Element *new_elements;

    if (tuple == NULL) {
        return false;
    }

    maximum_capacity = SIZE_MAX / sizeof(*tuple->elements);

    if (required > maximum_capacity) {
        return false;
    }

    if (required <= tuple->capacity) {
        return true;
    }

    if (tuple->capacity == 0) {
        new_capacity = maximum_capacity >= 4 ? 4 : required;
    } else {
        new_capacity = tuple->capacity;
    }

    if (new_capacity < required) {
        while (new_capacity < required) {
            if (new_capacity > maximum_capacity / 2) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2;
        }
    }

    new_elements = realloc(
        tuple->elements,
        new_capacity * sizeof(*tuple->elements)
    );

    if (new_elements == NULL) {
        return false;
    }

    tuple->elements = new_elements;
    tuple->capacity = new_capacity;
    return true;
}

static bool tuple_add_int(Tuple *tuple, int value)
{
    if (tuple == NULL || tuple->length == SIZE_MAX ||
        !tuple_reserve(tuple, tuple->length + 1)) {
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_INT;
    tuple->elements[tuple->length].data.integer = value;
    tuple->length++;

    return true;
}

static bool tuple_add_double(Tuple *tuple, double value)
{
    if (tuple == NULL || tuple->length == SIZE_MAX ||
        !tuple_reserve(tuple, tuple->length + 1)) {
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_DOUBLE;
    tuple->elements[tuple->length].data.real = value;
    tuple->length++;

    return true;
}

static bool tuple_add_char(Tuple *tuple, char value)
{
    if (tuple == NULL || tuple->length == SIZE_MAX ||
        !tuple_reserve(tuple, tuple->length + 1)) {
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_CHAR;
    tuple->elements[tuple->length].data.character = value;
    tuple->length++;

    return true;
}

static bool tuple_add_string(Tuple *tuple, const char *value, size_t length)
{
    char *copy;

    if (tuple == NULL || value == NULL || tuple->length == SIZE_MAX) {
        return false;
    }

    if (!duplicate_string(value, length, &copy)) {
        return false;
    }

    if (!tuple_reserve(tuple, tuple->length + 1)) {
        free(copy);
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_STRING;
    tuple->elements[tuple->length].data.string.data = copy;
    tuple->elements[tuple->length].data.string.length = length;
    tuple->length++;

    return true;
}

static void element_destroy(Element *element)
{
    if (element == NULL) {
        return;
    }

    if (element->type == VALUE_STRING) {
        free(element->data.string.data);
    }

    *element = (Element){0};
}

static bool tuple_remove_type(
    Tuple *tuple,
    ValueType type,
    size_t *removed
)
{
    size_t read_index;
    size_t write_index = 0;
    size_t removed_count = 0;

    if (tuple == NULL || removed == NULL || !value_type_is_valid(type)) {
        return false;
    }

    for (read_index = 0; read_index < tuple->length; read_index++) {
        if (tuple->elements[read_index].type == type) {
            element_destroy(&tuple->elements[read_index]);
            removed_count++;
        } else {
            if (write_index != read_index) {
                tuple->elements[write_index] =
                    tuple->elements[read_index];
                tuple->elements[read_index] = (Element){0};
            }

            write_index++;
        }
    }

    tuple->length = write_index;
    *removed = removed_count;

    return true;
}

static bool print_string_value(const StringValue *string)
{
    if (string == NULL || string->data == NULL) {
        return false;
    }

    if (fputc('"', stdout) == EOF) {
        return false;
    }

    if (string->length > 0 &&
        fwrite(string->data, 1, string->length, stdout) != string->length) {
        return false;
    }

    return fputc('"', stdout) != EOF;
}

static bool tuple_print(const Tuple *tuple)
{
    size_t index;

    if (tuple == NULL || fputc('(', stdout) == EOF) {
        return false;
    }

    for (index = 0; index < tuple->length; index++) {
        const Element *element = &tuple->elements[index];
        int result;

        if (index > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        switch (element->type) {
            case VALUE_INT:
                result = printf("%d", element->data.integer);
                if (result < 0) {
                    return false;
                }
                break;

            case VALUE_DOUBLE:
                result = printf("%g", element->data.real);
                if (result < 0) {
                    return false;
                }
                break;

            case VALUE_CHAR:
                result = printf("'%c'", element->data.character);
                if (result < 0) {
                    return false;
                }
                break;

            case VALUE_STRING:
                if (!print_string_value(&element->data.string)) {
                    return false;
                }
                break;

            default:
                return false;
        }
    }

    return fputs(")\n", stdout) != EOF;
}

static void tuple_destroy(Tuple *tuple)
{
    size_t index;

    if (tuple == NULL) {
        return;
    }

    for (index = 0; index < tuple->length; index++) {
        element_destroy(&tuple->elements[index]);
    }

    free(tuple->elements);
    tuple_init(tuple);
}

int main(void)
{
    Tuple tuple;
    size_t removed = 0;
    int status = EXIT_FAILURE;

    tuple_init(&tuple);

    if (!tuple_add_int(&tuple, 42) ||
        !tuple_add_string(&tuple, "alpha", sizeof("alpha") - 1) ||
        !tuple_add_double(&tuple, 3.14) ||
        !tuple_add_char(&tuple, 'X') ||
        !tuple_add_string(&tuple, "beta", sizeof("beta") - 1) ||
        !tuple_add_int(&tuple, 7)) {
        goto cleanup;
    }

    if (!tuple_print(&tuple)) {
        goto cleanup;
    }

    if (!tuple_remove_type(&tuple, VALUE_STRING, &removed)) {
        goto cleanup;
    }

    if (printf(
            "Removed %zu element%s\n",
            removed,
            removed == 1 ? "" : "s"
        ) < 0) {
        goto cleanup;
    }

    if (!tuple_print(&tuple)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    tuple_destroy(&tuple);
    return status;
}