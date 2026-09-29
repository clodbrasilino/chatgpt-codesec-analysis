#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int round_up_to_digits(double value, int digits, double *result)
{
    double scale;

    if (result == NULL || !isfinite(value) || digits < -308 || digits > 308) {
        return -1;
    }

    errno = 0;
    scale = pow(10.0, (double)digits);
    if (errno != 0 || !isfinite(scale) || scale == 0.0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'DBL_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'DBL_MAX'
     */
    if (fabs(value) > DBL_MAX / scale) {
        return -1;
    }

    *result = ceil(value * scale) / scale;
    return isfinite(*result) ? 0 : -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *value_end;
    char *digits_end;
    double value;
    double result;
    long digits;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <digits>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtod(argv[1], &value_end);
    if (errno != 0 || value_end == argv[1] || *value_end != '\0' || !isfinite(value)) {
        fputs("Invalid number\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    digits = strtol(argv[2], &digits_end, 10);
    if (errno != 0 || digits_end == argv[2] || *digits_end != '\0' ||
        digits < -308 || digits > 308) {
        fputs("Invalid digits\n", stderr);
        return EXIT_FAILURE;
    }

    if (round_up_to_digits(value, (int)digits, &result) != 0) {
        fputs("Rounding failed\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.*f\n", digits > 0 ? (int)digits : 0, result);
    return EXIT_SUCCESS;
}