#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double magnitude;
    double angle;
} Polar;

static int complex_to_polar(double real, double imaginary, Polar *result)
{
    if (result == NULL || !isfinite(real) || !isfinite(imaginary)) {
        return -1;
    }

    result->magnitude = hypot(real, imaginary);
    result->angle = atan2(imaginary, real);

    if (!isfinite(result->magnitude) || !isfinite(result->angle)) {
        return -1;
    }

    return 0;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed_value;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    parsed_value = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' || !isfinite(parsed_value)) {
        return -1;
    }

    *value = parsed_value;
    return 0;
}

int main(int argc, const char *const argv[])
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
        fprintf(stderr, "Invalid finite numeric input\n");
        return EXIT_FAILURE;
    }

    if (complex_to_polar(real, imaginary, &result) != 0) {
        fprintf(stderr, "Unable to convert to polar coordinates\n");
        return EXIT_FAILURE;
    }

    if (printf("Magnitude: %.17g\nAngle (radians): %.17g\n",
               result.magnitude, result.angle) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}