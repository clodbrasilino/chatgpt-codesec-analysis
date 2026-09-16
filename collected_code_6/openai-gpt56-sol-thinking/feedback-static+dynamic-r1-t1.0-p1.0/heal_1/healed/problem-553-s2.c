#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *integer_part;
    const char *fractional_part;
} DecimalTuple;

static bool tuple_to_double(const DecimalTuple *tuple, double *result)
{
    char *number;
    char *end;
    size_t integer_length;
    size_t fractional_length;
    size_t total_length;
    size_t i;
    double value;

    if (tuple == NULL || result == NULL ||
        tuple->integer_part == NULL ||
        tuple->fractional_part == NULL) {
        return false;
    }

    integer_length = strlen(tuple->integer_part);
    fractional_length = strlen(tuple->fractional_part);

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

    if (integer_length > SIZE_MAX - 2 ||
        fractional_length > SIZE_MAX - 2 - integer_length) {
        return false;
    }

    total_length = integer_length + fractional_length + 2;
    number = malloc(total_length);

    if (number == NULL) {
        return false;
    }

    memcpy(number, tuple->integer_part, integer_length);
    number[integer_length] = '.';
    memcpy(number + integer_length + 1,
           tuple->fractional_part,
           fractional_length);
    number[total_length - 1] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(number, &end);

    if (errno == ERANGE ||
        end == number ||
        *end != '\0' ||
        !isfinite(value)) {
        free(number);
        return false;
    }

    free(number);
    *result = value;

    return true;
}

int main(int argc, char * const argv[])
{
    DecimalTuple tuple;
    double value;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

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