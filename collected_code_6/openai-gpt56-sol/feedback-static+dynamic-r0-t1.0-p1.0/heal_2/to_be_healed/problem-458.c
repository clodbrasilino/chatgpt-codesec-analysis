#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int rectangle_area(double length, double width, double *area)
{
    if (area == NULL || !isfinite(length) || !isfinite(width) ||
        length < 0.0 || width < 0.0) {
        return 0;
    }

    *area = length * width;
    return isfinite(*area);
}

static int parse_dimension(const char *text, double *value)
{
    char *end = NULL;
    double parsed_value;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed_value = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(parsed_value) || parsed_value < 0.0) {
        return 0;
    }

    *value = parsed_value;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    double length;
    double width;
    double area;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <length> <width>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_dimension(argv[1], &length) ||
        !parse_dimension(argv[2], &width)) {
        fprintf(stderr,
                "Error: dimensions must be finite, non-negative numbers.\n");
        return EXIT_FAILURE;
    }

    if (!rectangle_area(length, width, &area)) {
        fprintf(stderr, "Error: unable to calculate a finite area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Area: %.17g\n", area) < 0) {
        fprintf(stderr, "Error: failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}