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
        tuple->integer_part == NULL || tuple->fractional_part == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    integer_length = strlen(tuple->integer_part);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    fractional_length = strlen(tuple->fractional_part);

    if (integer_length == 0 || fractional_length == 0) {
        return false;
    }

    i = 0;
    if (tuple->integer_part[0] == '+' || tuple->integer_part[0] == '-') {
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

    if (integer_length > SIZE_MAX - fractional_length - 2) {
        return false;
    }

    total_length = integer_length + fractional_length + 2;
    number = malloc(total_length);

    if (number == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(number, tuple->integer_part, integer_length);
    number[integer_length] = '.';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(number + integer_length + 1,
           tuple->fractional_part,
           fractional_length);
    number[total_length - 1] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(number, &end);

    if (errno == ERANGE || end == number || *end != '\0' || !isfinite(value)) {
        free(number);
        return false;
    }

    free(number);
    *result = value;
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    DecimalTuple tuple;
    double value;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer-part> <fractional-part>\n", argv[0]);
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