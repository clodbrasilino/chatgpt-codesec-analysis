#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long *values;
    size_t size;
    size_t capacity;
} IntTuple;

typedef enum {
    TUPLE_OK,
    TUPLE_INVALID_INPUT,
    TUPLE_OUT_OF_RANGE,
    TUPLE_NO_MEMORY
} TupleStatus;

static void tuple_destroy(IntTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->values);
    tuple->values = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
}

static TupleStatus tuple_append(IntTuple *tuple, long long value)
{
    if (tuple == NULL) {
        return TUPLE_INVALID_INPUT;
    }

    if (tuple->size == tuple->capacity) {
        const size_t maximum = SIZE_MAX / sizeof(*tuple->values);
        size_t new_capacity;
        long long *new_values;

        if (tuple->capacity >= maximum) {
            return TUPLE_NO_MEMORY;
        }

        if (tuple->capacity == 0) {
            new_capacity = maximum < 8 ? maximum : 8;
        } else if (tuple->capacity > maximum / 2) {
            new_capacity = maximum;
        } else {
            new_capacity = tuple->capacity * 2;
        }

        new_values = realloc(
            tuple->values,
            new_capacity * sizeof(*tuple->values)
        );

        if (new_values == NULL) {
            return TUPLE_NO_MEMORY;
        }

        tuple->values = new_values;
        tuple->capacity = new_capacity;
    }

    tuple->values[tuple->size] = value;
    ++tuple->size;

    return TUPLE_OK;
}

static TupleStatus string_to_tuple(const char *input, IntTuple *tuple)
{
    const char *current;

    if (input == NULL || tuple == NULL) {
        return TUPLE_INVALID_INPUT;
    }

    tuple->values = NULL;
    tuple->size = 0;
    tuple->capacity = 0;
    current = input;

    while (isspace((unsigned char)*current) != 0) {
        ++current;
    }

    while (*current != '\0') {
        char *end;
        long long value;
        int had_space = 0;
        TupleStatus status;

        errno = 0;
        value = strtoll(current, &end, 10);

        if (end == current) {
            tuple_destroy(tuple);
            return TUPLE_INVALID_INPUT;
        }

        if (errno == ERANGE) {
            tuple_destroy(tuple);
            return TUPLE_OUT_OF_RANGE;
        }

        status = tuple_append(tuple, value);
        if (status != TUPLE_OK) {
            tuple_destroy(tuple);
            return status;
        }

        current = end;

        while (isspace((unsigned char)*current) != 0) {
            had_space = 1;
            ++current;
        }

        if (*current == '\0') {
            break;
        }

        if (*current == ',') {
            ++current;

            while (isspace((unsigned char)*current) != 0) {
                ++current;
            }

            if (*current == '\0') {
                tuple_destroy(tuple);
                return TUPLE_INVALID_INPUT;
            }
        } else if (had_space == 0) {
            tuple_destroy(tuple);
            return TUPLE_INVALID_INPUT;
        }
    }

    return TUPLE_OK;
}

static int print_tuple(const IntTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return -1;
    }

    if (fputc('(', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < tuple->size; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fprintf(stdout, "%lld", tuple->values[i]) < 0) {
            return -1;
        }
    }

    if (fputs(")\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    IntTuple tuple = { NULL, 0, 0 };
    TupleStatus status;
    int result;

    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL
            ? argv[0]
            : "program";

        fprintf(stderr, "Usage: %s \"integer list\"\n", program_name);
        return EXIT_FAILURE;
    }

    status = string_to_tuple(argv[1], &tuple);

    switch (status) {
    case TUPLE_OK:
        break;

    case TUPLE_INVALID_INPUT:
        fputs("Invalid integer list\n", stderr);
        return EXIT_FAILURE;

    case TUPLE_OUT_OF_RANGE:
        fputs("Integer is out of range\n", stderr);
        return EXIT_FAILURE;

    case TUPLE_NO_MEMORY:
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;

    default:
        fputs("Unexpected conversion error\n", stderr);
        return EXIT_FAILURE;
    }

    result = print_tuple(&tuple);
    tuple_destroy(&tuple);

    if (result != 0) {
        fputs("Output operation failed\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}