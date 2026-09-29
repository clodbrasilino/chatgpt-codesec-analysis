#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *integer_part;
    const char *fractional_part;
} DecimalTuple;

bool tuple_to_double(const DecimalTuple *const tuple, double *const result)
{
    const char *integer;
    const char *fractional;
    long double whole = 0.0L;
    long double fraction = 0.0L;
    long double place = 0.1L;
    long double magnitude;
    bool negative = false;

    if (tuple == NULL || result == NULL ||
        tuple->integer_part == NULL || tuple->fractional_part == NULL) {
        return false;
    }

    integer = tuple->integer_part;
    fractional = tuple->fractional_part;

    if (*integer == '-' || *integer == '+') {
        negative = (*integer == '-');
        ++integer;
    }

    if (*integer == '\0' || *fractional == '\0') {
        return false;
    }

    while (*integer != '\0') {
        unsigned int digit;

        if (*integer < '0' || *integer > '9') {
            return false;
        }

        digit = (unsigned int)(*integer - '0');

        if (whole > (LDBL_MAX - (long double)digit) / 10.0L) {
            return false;
        }

        whole = whole * 10.0L + (long double)digit;

        if (!isfinite(whole)) {
            return false;
        }

        ++integer;
    }

    while (*fractional != '\0') {
        unsigned int digit;

        if (*fractional < '0' || *fractional > '9') {
            return false;
        }

        digit = (unsigned int)(*fractional - '0');

        if (place > 0.0L) {
            fraction += (long double)digit * place;

            if (!isfinite(fraction)) {
                return false;
            }

            place *= 0.1L;
        }

        ++fractional;
    }

    magnitude = whole + fraction;

    if (!isfinite(magnitude) || magnitude > (long double)DBL_MAX) {
        return false;
    }

    if (negative) {
        magnitude = -magnitude;
    }

    *result = (double)magnitude;
    return isfinite(*result);
}

int main(int argc, char **const argv)
{
    const char *program_name = "program";
    double value;

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <integer-part> <fractional-part>\n",
                program_name);
        return EXIT_FAILURE;
    }

    const DecimalTuple tuple = {
        .integer_part = argv[1],
        .fractional_part = argv[2]
    };

    if (!tuple_to_double(&tuple, &value)) {
        fprintf(stderr,
                "Invalid tuple or value outside the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("%.*g\n", DBL_DECIMAL_DIG, value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}