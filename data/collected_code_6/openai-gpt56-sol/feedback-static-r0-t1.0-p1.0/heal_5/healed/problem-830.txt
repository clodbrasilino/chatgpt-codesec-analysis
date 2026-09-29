#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int round_up_to_digits(double value, int digits, double *result)
{
    double factor;
    double scaled;
    double rounded;

    if (result == NULL || !isfinite(value) || digits < -308 || digits > 308) {
        return -1;
    }

    factor = pow(10.0, (double)digits);
    if (!isfinite(factor) || factor == 0.0) {
        return -1;
    }

    scaled = value * factor;
    if (!isfinite(scaled)) {
        return -1;
    }

    rounded = ceil(scaled) / factor;
    if (!isfinite(rounded)) {
        return -1;
    }

    *result = rounded;
    return 0;
}

int main(int argc, char *const argv[])
{
    const char *value_text;
    const char *digits_text;
    char *value_end;
    char *digits_end;
    double value;
    double result;
    long digits;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <digits>\n", argv[0]);
        return EXIT_FAILURE;
    }

    value_text = argv[1];
    digits_text = argv[2];

    errno = 0;
    value = strtod(value_text, &value_end);
    if (errno == ERANGE || value_end == value_text || *value_end != '\0' ||
        !isfinite(value)) {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    digits = strtol(digits_text, &digits_end, 10);
    if (errno == ERANGE || digits_end == digits_text || *digits_end != '\0' ||
        digits < -308L || digits > 308L) {
        fprintf(stderr, "Invalid digits value\n");
        return EXIT_FAILURE;
    }

    if (round_up_to_digits(value, (int)digits, &result) != 0) {
        fprintf(stderr, "Rounding failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%.*f\n", digits > 0L ? (int)digits : 0, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}