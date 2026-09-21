#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CHAR
} DataType;

typedef struct {
    const char *data;
    size_t length;
} StringValue;

typedef struct {
    DataType type;
    union {
        int integer;
        double real;
        StringValue string;
        char character;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
    size_t capacity;
} Tuple;

static bool data_type_is_valid(DataType type)
{
    return type == TYPE_INT ||
           type == TYPE_DOUBLE ||
           type == TYPE_STRING ||
           type == TYPE_CHAR;
}

static bool string_value_is_valid(const StringValue *string)
{
    if (string == NULL || string->data == NULL) {
        return false;
    }

    return memchr(string->data, '\0', string->length) == NULL;
}

static bool tuple_is_valid(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL || tuple->size > tuple->capacity) {
        return false;
    }

    if (tuple->capacity > 0 && tuple->elements == NULL) {
        return false;
    }

    for (i = 0; i < tuple->size; ++i) {
        const TupleElement *element = &tuple->elements[i];

        if (!data_type_is_valid(element->type)) {
            return false;
        }

        if (element->type == TYPE_STRING &&
            !string_value_is_valid(&element->value.string)) {
            return false;
        }
    }

    return true;
}

static bool remove_elements_by_type(Tuple *tuple, DataType target_type)
{
    size_t read_index;
    size_t write_index = 0;

    if (!data_type_is_valid(target_type) || !tuple_is_valid(tuple)) {
        return false;
    }

    for (read_index = 0; read_index < tuple->size; ++read_index) {
        if (tuple->elements[read_index].type != target_type) {
            if (write_index != read_index) {
                tuple->elements[write_index] = tuple->elements[read_index];
            }

            ++write_index;
        }
    }

    tuple->size = write_index;
    return true;
}

static bool print_string_value(const StringValue *string)
{
    if (!string_value_is_valid(string)) {
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

static bool print_tuple(const Tuple *tuple)
{
    size_t i;

    if (!tuple_is_valid(tuple) || fputc('(', stdout) == EOF) {
        return false;
    }

    for (i = 0; i < tuple->size; ++i) {
        const TupleElement *element = &tuple->elements[i];
        int result = 0;

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        switch (element->type) {
            case TYPE_INT:
                result = printf("%d", element->value.integer);
                break;

            case TYPE_DOUBLE:
                result = printf("%g", element->value.real);
                break;

            case TYPE_STRING:
                if (!print_string_value(&element->value.string)) {
                    return false;
                }
                continue;

            case TYPE_CHAR:
                result = printf("'%c'", element->value.character);
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

int main(void)
{
    static const char greeting[] = "hello";

    TupleElement elements[] = {
        {
            .type = TYPE_INT,
            .value.integer = 10
        },
        {
            .type = TYPE_DOUBLE,
            .value.real = 3.14
        },
        {
            .type = TYPE_STRING,
            .value.string = {
                .data = greeting,
                .length = sizeof(greeting) - 1
            }
        },
        {
            .type = TYPE_DOUBLE,
            .value.real = 2.71
        },
        {
            .type = TYPE_CHAR,
            .value.character = 'A'
        },
        {
            .type = TYPE_INT,
            .value.integer = 20
        }
    };

    Tuple tuple = {
        .elements = elements,
        .size = sizeof(elements) / sizeof(elements[0]),
        .capacity = sizeof(elements) / sizeof(elements[0])
    };

    if (fputs("Original tuple: ", stdout) == EOF ||
        !print_tuple(&tuple)) {
        return EXIT_FAILURE;
    }

    if (!remove_elements_by_type(&tuple, TYPE_DOUBLE)) {
        return EXIT_FAILURE;
    }

    if (fputs("Filtered tuple: ", stdout) == EOF ||
        !print_tuple(&tuple)) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}