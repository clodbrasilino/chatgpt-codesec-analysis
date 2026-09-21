#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *integer_part;
    const char *fractional_part;
} DecimalTuple;

bool tuple_to_double(const DecimalTuple *tuple, double *result)
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
        fraction += (long double)digit * place;

        if (!isfinite(fraction)) {
            return false;
        }

        place *= 0.1L;
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    double value;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer-part> <fractional-part>\n",
                argv[0]);
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

    printf("%.*g\n", DBL_DECIMAL_DIG, value);
    return EXIT_SUCCESS;
}