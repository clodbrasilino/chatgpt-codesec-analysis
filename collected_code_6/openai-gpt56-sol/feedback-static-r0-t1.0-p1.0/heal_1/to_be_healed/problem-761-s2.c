#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_arc_length(double radius, double angle_degrees, double *result)
{
    const double pi = acos(-1.0);

    if (result == NULL || !isfinite(radius) || !isfinite(angle_degrees) ||
        radius < 0.0) {
        return -1;
    }

    *result = radius * angle_degrees * pi / 180.0;

    return isfinite(*result) ? 0 : -1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    double radius;
    double angle_degrees;
    double arc_length;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <angle_degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &radius) != 0 ||
        parse_double(argv[2], &angle_degrees) != 0) {
        fprintf(stderr, "Error: arguments must be finite numbers.\n");
        return EXIT_FAILURE;
    }

    if (calculate_arc_length(radius, angle_degrees, &arc_length) != 0) {
        fprintf(stderr, "Error: radius must be nonnegative and the result must be finite.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", arc_length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}