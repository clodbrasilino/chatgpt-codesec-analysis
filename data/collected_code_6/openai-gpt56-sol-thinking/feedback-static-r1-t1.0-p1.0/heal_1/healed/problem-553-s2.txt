#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COMPONENT_LENGTH ((size_t)1048576)

typedef struct {
    const char *integer_part;
    size_t integer_length;
    const char *fractional_part;
    size_t fractional_length;
} DecimalTuple;

static bool bounded_length(const char *text, size_t *length)
{
    size_t i;

    if (text == NULL || length == NULL) {
        return false;
    }

    for (i = 0; i < MAX_COMPONENT_LENGTH; ++i) {
        if (text[i] == '\0') {
            *length = i;
            return true;
        }
    }

    return false;
}

static bool tuple_to_double(const DecimalTuple *tuple, double *result)
{
    char *number;
    char *end;
    size_t combined_length;
    size_t total_length;
    size_t i;
    double value;

    if (tuple == NULL || result == NULL ||
        tuple->integer_part == NULL ||
        tuple->fractional_part == NULL) {
        return false;
    }

    if (tuple->integer_length == 0 || tuple->fractional_length == 0) {
        return false;
    }

    i = 0;
    if (tuple->integer_part[0] == '+' ||
        tuple->integer_part[0] == '-') {
        i = 1;
    }

    if (i == tuple->integer_length) {
        return false;
    }

    for (; i < tuple->integer_length; ++i) {
        if (tuple->integer_part[i] < '0' ||
            tuple->integer_part[i] > '9') {
            return false;
        }
    }

    for (i = 0; i < tuple->fractional_length; ++i) {
        if (tuple->fractional_part[i] < '0' ||
            tuple->fractional_part[i] > '9') {
            return false;
        }
    }

    if (tuple->fractional_length >
        SIZE_MAX - tuple->integer_length) {
        return false;
    }

    combined_length =
        tuple->integer_length + tuple->fractional_length;

    if (combined_length > SIZE_MAX - 2) {
        return false;
    }

    total_length = combined_length + 2;
    number = malloc(total_length);

    if (number == NULL) {
        return false;
    }

    for (i = 0; i < tuple->integer_length; ++i) {
        number[i] = tuple->integer_part[i];
    }

    number[tuple->integer_length] = '.';

    for (i = 0; i < tuple->fractional_length; ++i) {
        number[tuple->integer_length + 1 + i] =
            tuple->fractional_part[i];
    }

    number[total_length - 1] = '\0';

    errno = 0;
    value = strtod(number, &end);

    if (errno == ERANGE || end == number ||
        *end != '\0' || !isfinite(value)) {
        free(number);
        return false;
    }

    free(number);
    *result = value;
    return true;
}

int main(int argc, char *const argv[])
{
    DecimalTuple tuple;
    const char *program_name;
    double value;

    program_name =
        argc > 0 && argv != NULL && argv[0] != NULL
            ? argv[0]
            : "program";

    if (argc != 3 || argv == NULL) {
        fprintf(stderr,
                "Usage: %s <integer-part> <fractional-part>\n",
                program_name);
        return EXIT_FAILURE;
    }

    tuple.integer_part = argv[1];
    tuple.fractional_part = argv[2];

    if (!bounded_length(tuple.integer_part,
                        &tuple.integer_length) ||
        !bounded_length(tuple.fractional_part,
                        &tuple.fractional_length)) {
        fprintf(stderr, "Input is missing or too long\n");
        return EXIT_FAILURE;
    }

    if (!tuple_to_double(&tuple, &value)) {
        fprintf(stderr, "Invalid tuple or conversion failure\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", value);
    return EXIT_SUCCESS;
}