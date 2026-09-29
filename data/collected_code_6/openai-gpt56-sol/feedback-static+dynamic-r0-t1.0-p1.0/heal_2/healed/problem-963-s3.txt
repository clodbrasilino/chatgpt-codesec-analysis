#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_discriminant(double a, double b, double c, double *result)
{
    double discriminant;

    if (result == NULL || !isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    discriminant = fma(b, b, -4.0 * a * c);

    if (!isfinite(discriminant)) {
        return 0;
    }

    *result = discriminant;
    return 1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' || !isfinite(parsed)) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(int argc, const char *const argv[])
{
    double a;
    double b;
    double c;
    double discriminant;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_double(argv[1], &a) ||
        !parse_double(argv[2], &b) ||
        !parse_double(argv[3], &c)) {
        fputs("Invalid coefficient.\n", stderr);
        return EXIT_FAILURE;
    }

    if (a == 0.0) {
        fputs("Coefficient a must be nonzero.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_discriminant(a, b, c, &discriminant)) {
        fputs("Unable to calculate a finite discriminant.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.17g\n", discriminant);
    return EXIT_SUCCESS;
}