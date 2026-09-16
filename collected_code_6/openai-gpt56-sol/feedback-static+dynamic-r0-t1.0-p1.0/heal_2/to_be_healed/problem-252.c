#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double magnitude;
    double angle;
} Polar;

static int to_polar(double real, double imaginary, Polar *result)
{
    if (result == NULL || !isfinite(real) || !isfinite(imaginary)) {
        return -1;
    }

    result->magnitude = hypot(real, imaginary);
    result->angle = atan2(imaginary, real);

    return isfinite(result->magnitude) && isfinite(result->angle) ? 0 : -1;
}

static int parse_double(const char *text, double *value)
{
    char *end;
    double parsed;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    double real;
    double imaginary;
    Polar result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <real> <imaginary>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &real) != 0 ||
        parse_double(argv[2], &imaginary) != 0) {
        fputs("Invalid numeric input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (to_polar(real, imaginary, &result) != 0) {
        fputs("Unable to convert the complex number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Magnitude: %.17g\nAngle (radians): %.17g\n",
               result.magnitude, result.angle) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}