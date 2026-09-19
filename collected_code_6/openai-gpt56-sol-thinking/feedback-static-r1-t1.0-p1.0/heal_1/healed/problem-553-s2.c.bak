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

static bool is_digit_string(const char *text, size_t start, size_t length)
{
    size_t i;

    for (i = start; i < length; ++i) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }

    return true;
}

static bool tuple_to_double(const DecimalTuple *tuple, double *result)
{
    const char *integer_part;
    const char *fractional_part;
    char *number;
    char *end;
    size_t integer_length;
    size_t fractional_length;
    size_t content_length;
    size_t total_length;
    size_t integer_start;
    double value;

    if (tuple == NULL || result == NULL ||
        tuple->integer_part == NULL || tuple->fractional_part == NULL) {
        return false;
    }

    integer_part = tuple->integer_part;
    fractional_part = tuple->fractional_part;
    integer_length = strlen(integer_part);
    fractional_length = strlen(fractional_part);

    if (integer_length == 0 || fractional_length == 0) {
        return false;
    }

    integer_start = 0;
    if (integer_part[0] == '+' || integer_part[0] == '-') {
        integer_start = 1;
    }

    if (integer_start == integer_length ||
        !is_digit_string(integer_part, integer_start, integer_length) ||
        !is_digit_string(fractional_part, 0, fractional_length)) {
        return false;
    }

    if (fractional_length > SIZE_MAX - integer_length) {
        return false;
    }

    content_length = integer_length + fractional_length;

    if (content_length > SIZE_MAX - 2) {
        return false;
    }

    total_length = content_length + 2;
    number = malloc(total_length);

    if (number == NULL) {
        return false;
    }

    memcpy(number, integer_part, integer_length);
    number[integer_length] = '.';
    memcpy(number + integer_length + 1, fractional_part, fractional_length);
    number[total_length - 1] = '\0';

    errno = 0;
    value = strtod(number, &end);

    if (errno == ERANGE || end == number || *end != '\0' || !isfinite(value)) {
        free(number);
        return false;
    }

    free(number);
    *result = value;
    return true;
}

int main(int argc, char *argv[const])
{
    const char *program_name;
    DecimalTuple tuple;
    double value;

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
        fputs("Invalid tuple or conversion failure\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", value);
    return EXIT_SUCCESS;
}