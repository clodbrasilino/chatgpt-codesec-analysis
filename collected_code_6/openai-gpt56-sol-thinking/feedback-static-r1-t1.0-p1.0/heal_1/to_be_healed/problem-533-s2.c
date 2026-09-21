#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VALUE_INT,
    VALUE_DOUBLE,
    VALUE_CHAR,
    VALUE_STRING
} ValueType;

typedef struct {
    ValueType type;
    union {
        int integer;
        double real;
        char character;
        char *string;
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

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    return copy;
}

static bool tuple_reserve(Tuple *tuple, size_t required)
{
    size_t new_capacity;
    Element *new_elements;

    if (tuple == NULL) {
        return false;
    }

    if (required <= tuple->capacity) {
        return true;
    }

    if (required > SIZE_MAX / sizeof(*tuple->elements)) {
        return false;
    }

    new_capacity = tuple->capacity == 0 ? 4 : tuple->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*tuple->elements)) {
        return false;
    }

    new_elements = realloc(tuple->elements,
                           new_capacity * sizeof(*tuple->elements));
    if (new_elements == NULL) {
        return false;
    }

    tuple->elements = new_elements;
    tuple->capacity = new_capacity;
    return true;
}

static bool tuple_add_int(Tuple *tuple, int value)
{
    if (tuple == NULL || !tuple_reserve(tuple, tuple->length + 1)) {
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_INT;
    tuple->elements[tuple->length].data.integer = value;
    tuple->length++;
    return true;
}

static bool tuple_add_double(Tuple *tuple, double value)
{
    if (tuple == NULL || !tuple_reserve(tuple, tuple->length + 1)) {
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_DOUBLE;
    tuple->elements[tuple->length].data.real = value;
    tuple->length++;
    return true;
}

static bool tuple_add_char(Tuple *tuple, char value)
{
    if (tuple == NULL || !tuple_reserve(tuple, tuple->length + 1)) {
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_CHAR;
    tuple->elements[tuple->length].data.character = value;
    tuple->length++;
    return true;
}

static bool tuple_add_string(Tuple *tuple, const char *value)
{
    char *copy;

    if (tuple == NULL || value == NULL ||
        !tuple_reserve(tuple, tuple->length + 1)) {
        return false;
    }

    copy = duplicate_string(value);
    if (copy == NULL) {
        return false;
    }

    tuple->elements[tuple->length].type = VALUE_STRING;
    tuple->elements[tuple->length].data.string = copy;
    tuple->length++;
    return true;
}

static void element_destroy(Element *element)
{
    if (element == NULL) {
        return;
    }

    if (element->type == VALUE_STRING) {
        free(element->data.string);
    }

    memset(element, 0, sizeof(*element));
}

bool tuple_remove_type(Tuple *tuple, ValueType type, size_t *removed)
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
                tuple->elements[write_index] = tuple->elements[read_index];
                memset(&tuple->elements[read_index], 0,
                       sizeof(tuple->elements[read_index]));
            }
            write_index++;
        }
    }

    tuple->length = write_index;
    *removed = removed_count;
    return true;
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
                break;
            case VALUE_DOUBLE:
                result = printf("%g", element->data.real);
                break;
            case VALUE_CHAR:
                result = printf("'%c'", element->data.character);
                break;
            case VALUE_STRING:
                result = printf("\"%s\"", element->data.string);
                break;
            default:
                return false;
        }

        if (result < 0) {
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
        !tuple_add_string(&tuple, "alpha") ||
        !tuple_add_double(&tuple, 3.14) ||
        !tuple_add_char(&tuple, 'X') ||
        !tuple_add_string(&tuple, "beta") ||
        !tuple_add_int(&tuple, 7)) {
        goto cleanup;
    }

    if (!tuple_print(&tuple)) {
        goto cleanup;
    }

    if (!tuple_remove_type(&tuple, VALUE_STRING, &removed)) {
        goto cleanup;
    }

    if (printf("Removed %zu element%s\n",
               removed, removed == 1 ? "" : "s") < 0) {
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