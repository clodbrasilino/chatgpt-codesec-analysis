#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t count;
} IntTuple;

typedef enum {
    TUPLE_SUCCESS,
    TUPLE_INVALID_INPUT,
    TUPLE_OUT_OF_MEMORY
} TupleStatus;

void tuple_destroy(IntTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->values);
    tuple->values = NULL;
    tuple->count = 0;
}

static TupleStatus tuple_append(
    IntTuple *tuple,
    size_t *capacity,
    int value
)
{
    if (tuple->count == *capacity) {
        size_t new_capacity;
        int *new_values;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return TUPLE_OUT_OF_MEMORY;
            }

            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*tuple->values)) {
            return TUPLE_OUT_OF_MEMORY;
        }

        new_values = realloc(
            tuple->values,
            new_capacity * sizeof(*tuple->values)
        );

        if (new_values == NULL) {
            return TUPLE_OUT_OF_MEMORY;
        }

        tuple->values = new_values;
        *capacity = new_capacity;
    }

    tuple->values[tuple->count] = value;
    ++tuple->count;

    return TUPLE_SUCCESS;
}

TupleStatus string_to_tuple(const char *input, IntTuple *tuple)
{
    IntTuple result = { NULL, 0 };
    const char *cursor;
    size_t capacity = 0;

    if (tuple == NULL) {
        return TUPLE_INVALID_INPUT;
    }

    tuple->values = NULL;
    tuple->count = 0;

    if (input == NULL) {
        return TUPLE_INVALID_INPUT;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor == '\0') {
        return TUPLE_INVALID_INPUT;
    }

    for (;;) {
        char *end;
        long parsed_value;
        const char *separator_start;
        TupleStatus status;

        errno = 0;
        parsed_value = strtol(cursor, &end, 10);

        if (end == cursor ||
            errno == ERANGE ||
            parsed_value < INT_MIN ||
            parsed_value > INT_MAX) {
            tuple_destroy(&result);
            return TUPLE_INVALID_INPUT;
        }

        status = tuple_append(&result, &capacity, (int)parsed_value);

        if (status != TUPLE_SUCCESS) {
            tuple_destroy(&result);
            return status;
        }

        cursor = end;
        separator_start = cursor;

        while (isspace((unsigned char)*cursor) != 0) {
            ++cursor;
        }

        if (*cursor == '\0') {
            *tuple = result;
            return TUPLE_SUCCESS;
        }

        if (*cursor == ',') {
            ++cursor;

            while (isspace((unsigned char)*cursor) != 0) {
                ++cursor;
            }

            if (*cursor == '\0') {
                tuple_destroy(&result);
                return TUPLE_INVALID_INPUT;
            }
        } else if (cursor == separator_start) {
            tuple_destroy(&result);
            return TUPLE_INVALID_INPUT;
        }
    }
}

int print_tuple(const IntTuple *tuple)
{
    size_t index;

    if (tuple == NULL ||
        (tuple->count != 0 && tuple->values == NULL)) {
        return -1;
    }

    if (fputc('(', stdout) == EOF) {
        return -1;
    }

    for (index = 0; index < tuple->count; ++index) {
        if (index != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("%d", tuple->values[index]) < 0) {
            return -1;
        }
    }

    if (tuple->count == 1 && fputc(',', stdout) == EOF) {
        return -1;
    }

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    IntTuple tuple = { NULL, 0 };
    TupleStatus status;
    const char *program_name;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "tuple";

    if (argc != 2 || argv == NULL) {
        fprintf(stderr, "Usage: %s \"integer list\"\n", program_name);
        return EXIT_FAILURE;
    }

    status = string_to_tuple(argv[1], &tuple);

    if (status == TUPLE_INVALID_INPUT) {
        fputs("Invalid integer list\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == TUPLE_OUT_OF_MEMORY) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_tuple(&tuple) != 0) {
        tuple_destroy(&tuple);
        fputs("Output failed\n", stderr);
        return EXIT_FAILURE;
    }

    tuple_destroy(&tuple);
    return EXIT_SUCCESS;
}