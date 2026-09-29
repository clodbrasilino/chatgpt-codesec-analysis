#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MAX_COMPONENT_LENGTH = 4096,
    NUMBER_BUFFER_SIZE = (MAX_COMPONENT_LENGTH * 2) + 2
};

typedef struct {
    const char *integer_part;
    const char *fractional_part;
} DecimalTuple;

static bool bounded_string_length(const char *text, size_t limit, size_t *length)
{
    size_t i;

    if (text == NULL || length == NULL) {
        return false;
    }

    for (i = 0; i <= limit; ++i) {
        if (text[i] == '\0') {
            *length = i;
            return true;
        }
    }

    return false;
}

static bool tuple_to_double(const DecimalTuple *tuple, double *result)
{
    char number[NUMBER_BUFFER_SIZE];
    char *end;
    size_t integer_length;
    size_t fractional_length;
    size_t position;
    size_t i;
    double value;

    if (tuple == NULL || result == NULL ||
        tuple->integer_part == NULL || tuple->fractional_part == NULL) {
        return false;
    }

    if (!bounded_string_length(tuple->integer_part,
                               MAX_COMPONENT_LENGTH,
                               &integer_length) ||
        !bounded_string_length(tuple->fractional_part,
                               MAX_COMPONENT_LENGTH,
                               &fractional_length)) {
        return false;
    }

    if (integer_length == 0 || fractional_length == 0) {
        return false;
    }

    i = 0;
    if (tuple->integer_part[0] == '+' ||
        tuple->integer_part[0] == '-') {
        i = 1;
    }

    if (i == integer_length) {
        return false;
    }

    for (; i < integer_length; ++i) {
        if (tuple->integer_part[i] < '0' ||
            tuple->integer_part[i] > '9') {
            return false;
        }
    }

    for (i = 0; i < fractional_length; ++i) {
        if (tuple->fractional_part[i] < '0' ||
            tuple->fractional_part[i] > '9') {
            return false;
        }
    }

    if (integer_length > sizeof(number) - 2 ||
        fractional_length > sizeof(number) - integer_length - 2) {
        return false;
    }

    position = 0;

    for (i = 0; i < integer_length; ++i) {
        number[position++] = tuple->integer_part[i];
    }

    number[position++] = '.';

    for (i = 0; i < fractional_length; ++i) {
        number[position++] = tuple->fractional_part[i];
    }

    number[position] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(number, &end);

    if (errno == ERANGE || end == number || *end != '\0' ||
        !isfinite(value)) {
        return false;
    }

    *result = value;
    return true;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    DecimalTuple tuple;
    double value;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <integer-part> <fractional-part>\n",
                program_name);
        return EXIT_FAILURE;
    }

    tuple.integer_part = argv[1];
    tuple.fractional_part = argv[2];

    if (!tuple_to_double(&tuple, &value)) {
        fprintf(stderr, "Invalid tuple or conversion failure\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", value);
    return EXIT_SUCCESS;
}