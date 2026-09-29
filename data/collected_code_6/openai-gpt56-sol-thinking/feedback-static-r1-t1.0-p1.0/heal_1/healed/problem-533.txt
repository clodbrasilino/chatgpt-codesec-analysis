#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    DATA_TYPE_INVALID = 0,
    DATA_TYPE_INTEGER,
    DATA_TYPE_DOUBLE,
    DATA_TYPE_CHARACTER,
    DATA_TYPE_STRING,
    DATA_TYPE_COUNT
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
        char character;
        StringValue string;
    } data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
} Tuple;

bool tuple_remove_type(Tuple *tuple, DataType target_type, size_t *removed_count)
{
    size_t read_index;
    size_t write_index = 0;
    size_t original_size;

    if (tuple == NULL || removed_count == NULL) {
        return false;
    }

    if (target_type <= DATA_TYPE_INVALID || target_type >= DATA_TYPE_COUNT) {
        return false;
    }

    if (tuple->size > 0 && tuple->elements == NULL) {
        return false;
    }

    original_size = tuple->size;

    for (read_index = 0; read_index < original_size; ++read_index) {
        if (tuple->elements[read_index].type != target_type) {
            if (write_index != read_index) {
                tuple->elements[write_index] = tuple->elements[read_index];
            }
            ++write_index;
        }
    }

    for (read_index = write_index; read_index < original_size; ++read_index) {
        tuple->elements[read_index] = (TupleElement){0};
    }

    tuple->size = write_index;
    *removed_count = original_size - write_index;

    return true;
}

static bool print_string_value(const StringValue *string)
{
    if (string == NULL || (string->length > 0 && string->data == NULL)) {
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

bool print_tuple(const Tuple *tuple)
{
    size_t index;
    int result;

    if (tuple == NULL || (tuple->size > 0 && tuple->elements == NULL)) {
        return false;
    }

    if (fputc('(', stdout) == EOF) {
        return false;
    }

    for (index = 0; index < tuple->size; ++index) {
        if (index > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        switch (tuple->elements[index].type) {
            case DATA_TYPE_INTEGER:
                result = printf("%d", tuple->elements[index].data.integer);
                if (result < 0) {
                    return false;
                }
                break;

            case DATA_TYPE_DOUBLE:
                result = printf("%.2f", tuple->elements[index].data.real);
                if (result < 0) {
                    return false;
                }
                break;

            case DATA_TYPE_CHARACTER:
                result = printf("'%c'", tuple->elements[index].data.character);
                if (result < 0) {
                    return false;
                }
                break;

            case DATA_TYPE_STRING:
                if (!print_string_value(&tuple->elements[index].data.string)) {
                    return false;
                }
                break;

            default:
                return false;
        }
    }

    return fputs(")\n", stdout) != EOF;
}

int main(void)
{
    TupleElement elements[] = {
        {
            .type = DATA_TYPE_INTEGER,
            .data.integer = 42
        },
        {
            .type = DATA_TYPE_DOUBLE,
            .data.real = 3.14
        },
        {
            .type = DATA_TYPE_STRING,
            .data.string = {
                .data = "example",
                .length = sizeof("example") - 1
            }
        },
        {
            .type = DATA_TYPE_DOUBLE,
            .data.real = 7.25
        },
        {
            .type = DATA_TYPE_CHARACTER,
            .data.character = 'A'
        },
        {
            .type = DATA_TYPE_INTEGER,
            .data.integer = 100
        }
    };

    Tuple tuple = {
        .elements = elements,
        .size = sizeof(elements) / sizeof(elements[0])
    };

    size_t removed_count = 0;

    if (!tuple_remove_type(&tuple, DATA_TYPE_DOUBLE, &removed_count)) {
        fputs("Failed to remove tuple elements\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_tuple(&tuple)) {
        fputs("Failed to print tuple\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Removed elements: %zu\n", removed_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}