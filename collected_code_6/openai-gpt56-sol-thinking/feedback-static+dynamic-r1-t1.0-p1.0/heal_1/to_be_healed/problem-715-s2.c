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
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->count = 0;
    }
}

TupleStatus string_to_tuple(const char *input, IntTuple *tuple)
{
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

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0') {
        return TUPLE_INVALID_INPUT;
    }

    for (;;) {
        char *end;
        long value;
        const char *separator_start;

        errno = 0;
        value = strtol(cursor, &end, 10);

        if (end == cursor || errno == ERANGE || value < INT_MIN || value > INT_MAX) {
            tuple_destroy(tuple);
            return TUPLE_INVALID_INPUT;
        }

        if (tuple->count == capacity) {
            size_t new_capacity;
            int *new_values;

            if (capacity == 0) {
                new_capacity = 8;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    tuple_destroy(tuple);
                    return TUPLE_OUT_OF_MEMORY;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*tuple->values)) {
                tuple_destroy(tuple);
                return TUPLE_OUT_OF_MEMORY;
            }

            new_values = realloc(tuple->values,
                                 new_capacity * sizeof(*tuple->values));
            if (new_values == NULL) {
                tuple_destroy(tuple);
                return TUPLE_OUT_OF_MEMORY;
            }

            tuple->values = new_values;
            capacity = new_capacity;
        }

        tuple->values[tuple->count++] = (int)value;
        cursor = end;
        separator_start = cursor;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            return TUPLE_SUCCESS;
        }

        if (*cursor == ',') {
            ++cursor;

            while (isspace((unsigned char)*cursor)) {
                ++cursor;
            }

            if (*cursor == '\0') {
                tuple_destroy(tuple);
                return TUPLE_INVALID_INPUT;
            }
        } else if (cursor == separator_start) {
            tuple_destroy(tuple);
            return TUPLE_INVALID_INPUT;
        }
    }
}

int print_tuple(const IntTuple *tuple)
{
    size_t i;

    if (tuple == NULL || (tuple->count > 0 && tuple->values == NULL)) {
        return -1;
    }

    if (fputc('(', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("%d", tuple->values[i]) < 0) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    IntTuple tuple;
    TupleStatus status;
    int print_status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"integer list\"\n", argv[0]);
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

    print_status = print_tuple(&tuple);
    tuple_destroy(&tuple);

    if (print_status != 0) {
        fputs("Output failed\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}