#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_CAPACITY 64

typedef enum {
    DATA_TYPE_INVALID = 0,
    DATA_TYPE_INTEGER,
    DATA_TYPE_DOUBLE,
    DATA_TYPE_CHARACTER,
    DATA_TYPE_STRING,
    DATA_TYPE_COUNT
} DataType;

typedef struct {
    DataType type;
    union {
        int integer;
        double real;
        char character;
        char string[STRING_CAPACITY];
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
        memset(&tuple->elements[read_index], 0, sizeof(tuple->elements[read_index]));
    }

    tuple->size = write_index;
    *removed_count = original_size - write_index;
    return true;
}

bool print_tuple(const Tuple *tuple)
{
    size_t index;
    int result;

    if (tuple == NULL || (tuple->size > 0 && tuple->elements == NULL)) {
        return false;
    }

    if (printf("(") < 0) {
        return false;
    }

    for (index = 0; index < tuple->size; ++index) {
        if (index > 0 && printf(", ") < 0) {
            return false;
        }

        switch (tuple->elements[index].type) {
            case DATA_TYPE_INTEGER:
                result = printf("%d", tuple->elements[index].data.integer);
                break;
            case DATA_TYPE_DOUBLE:
                result = printf("%.2f", tuple->elements[index].data.real);
                break;
            case DATA_TYPE_CHARACTER:
                result = printf("'%c'", tuple->elements[index].data.character);
                break;
            case DATA_TYPE_STRING:
                result = printf("\"%.*s\"", STRING_CAPACITY,
                                tuple->elements[index].data.string);
                break;
            default:
                return false;
        }

        if (result < 0) {
            return false;
        }
    }

    return printf(")\n") >= 0;
}

int main(void)
{
    TupleElement elements[] = {
        { .type = DATA_TYPE_INTEGER, .data.integer = 42 },
        { .type = DATA_TYPE_DOUBLE, .data.real = 3.14 },
        { .type = DATA_TYPE_STRING, .data.string = "example" },
        { .type = DATA_TYPE_DOUBLE, .data.real = 7.25 },
        { .type = DATA_TYPE_CHARACTER, .data.character = 'A' },
        { .type = DATA_TYPE_INTEGER, .data.integer = 100 }
    };
    Tuple tuple = {
        .elements = elements,
        .size = sizeof(elements) / sizeof(elements[0])
    };
    size_t removed_count = 0;

    if (!tuple_remove_type(&tuple, DATA_TYPE_DOUBLE, &removed_count)) {
        fprintf(stderr, "Failed to remove tuple elements\n");
        return EXIT_FAILURE;
    }

    if (!print_tuple(&tuple)) {
        fprintf(stderr, "Failed to print tuple\n");
        return EXIT_FAILURE;
    }

    if (printf("Removed elements: %zu\n", removed_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}