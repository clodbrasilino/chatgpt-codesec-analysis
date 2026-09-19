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
    TUPLE_OK,
    TUPLE_INVALID_ARGUMENT,
    TUPLE_INVALID_FORMAT,
    TUPLE_OUT_OF_RANGE,
    TUPLE_NO_MEMORY
} TupleStatus;

void tuple_destroy(IntTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->count = 0;
    }
}

static TupleStatus tuple_append(IntTuple *tuple, size_t *capacity, int value)
{
    size_t new_capacity;
    int *new_values;

    if (tuple == NULL || capacity == NULL) {
        return TUPLE_INVALID_ARGUMENT;
    }

    if (tuple->count < *capacity) {
        tuple->values[tuple->count++] = value;
        return TUPLE_OK;
    }

    if (*capacity == 0) {
        new_capacity = 8;
    } else {
        if (*capacity > SIZE_MAX / 2) {
            return TUPLE_NO_MEMORY;
        }

        new_capacity = *capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*tuple->values)) {
        return TUPLE_NO_MEMORY;
    }

    new_values = realloc(
        tuple->values,
        new_capacity * sizeof(*tuple->values)
    );

    if (new_values == NULL) {
        return TUPLE_NO_MEMORY;
    }

    tuple->values = new_values;
    *capacity = new_capacity;
    tuple->values[tuple->count++] = value;

    return TUPLE_OK;
}

static void tuple_commit(IntTuple *result, IntTuple *temporary)
{
    tuple_destroy(result);
    *result = *temporary;
    temporary->values = NULL;
    temporary->count = 0;
}

TupleStatus string_to_tuple(const char *text, IntTuple *result)
{
    IntTuple temporary = {NULL, 0};
    TupleStatus status;
    const char *cursor;
    char *end;
    char closing = '\0';
    size_t capacity = 0;

    if (text == NULL || result == NULL) {
        return TUPLE_INVALID_ARGUMENT;
    }

    cursor = text;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '(') {
        closing = ')';
        ++cursor;
    } else if (*cursor == '[') {
        closing = ']';
        ++cursor;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (closing != '\0' && *cursor == closing) {
        ++cursor;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor != '\0') {
            return TUPLE_INVALID_FORMAT;
        }

        tuple_commit(result, &temporary);
        return TUPLE_OK;
    }

    if (*cursor == '\0') {
        if (closing != '\0') {
            return TUPLE_INVALID_FORMAT;
        }

        tuple_commit(result, &temporary);
        return TUPLE_OK;
    }

    for (;;) {
        long value;
        int had_whitespace = 0;

        errno = 0;
        value = strtol(cursor, &end, 10);

        if (end == cursor) {
            status = TUPLE_INVALID_FORMAT;
            break;
        }

        if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
            status = TUPLE_OUT_OF_RANGE;
            break;
        }

        status = tuple_append(&temporary, &capacity, (int)value);
        if (status != TUPLE_OK) {
            break;
        }

        cursor = end;

        while (isspace((unsigned char)*cursor)) {
            had_whitespace = 1;
            ++cursor;
        }

        if (closing != '\0' && *cursor == closing) {
            ++cursor;

            while (isspace((unsigned char)*cursor)) {
                ++cursor;
            }

            if (*cursor != '\0') {
                status = TUPLE_INVALID_FORMAT;
                break;
            }

            tuple_commit(result, &temporary);
            return TUPLE_OK;
        }

        if (*cursor == '\0') {
            if (closing != '\0') {
                status = TUPLE_INVALID_FORMAT;
                break;
            }

            tuple_commit(result, &temporary);
            return TUPLE_OK;
        }

        if (*cursor == ',') {
            ++cursor;

            while (isspace((unsigned char)*cursor)) {
                ++cursor;
            }

            continue;
        }

        if (!had_whitespace) {
            status = TUPLE_INVALID_FORMAT;
            break;
        }
    }

    tuple_destroy(&temporary);
    return status;
}

static int print_tuple(const IntTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return 0;
    }

    if (fputc('(', stdout) == EOF) {
        return 0;
    }

    for (i = 0; i < tuple->count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (fprintf(stdout, "%d", tuple->values[i]) < 0) {
            return 0;
        }
    }

    return fputs(")\n", stdout) != EOF;
}

static const char *tuple_status_message(TupleStatus status)
{
    switch (status) {
        case TUPLE_OK:
            return "success";
        case TUPLE_INVALID_ARGUMENT:
            return "invalid argument";
        case TUPLE_INVALID_FORMAT:
            return "invalid integer-list format";
        case TUPLE_OUT_OF_RANGE:
            return "integer is outside the supported range";
        case TUPLE_NO_MEMORY:
            return "memory allocation failed";
        default:
            return "unknown error";
    }
}

int main(int argc, char *const argv[])
{
    IntTuple tuple = {NULL, 0};
    TupleStatus status;
    int success;

    if (argc != 2) {
        fprintf(
            stderr,
            "Usage: %s \"1, 2, 3\"\n",
            argc > 0 ? argv[0] : "tuple"
        );
        return EXIT_FAILURE;
    }

    status = string_to_tuple(argv[1], &tuple);

    if (status != TUPLE_OK) {
        fprintf(
            stderr,
            "Conversion failed: %s\n",
            tuple_status_message(status)
        );
        tuple_destroy(&tuple);
        return EXIT_FAILURE;
    }

    success = print_tuple(&tuple);
    tuple_destroy(&tuple);

    if (!success || fflush(stdout) == EOF) {
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}