#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int calculate_parallelogram_area(double base, double height, double *area)
{
    if (area == NULL || !isfinite(base) || !isfinite(height) ||
        base < 0.0 || height < 0.0) {
        return 0;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'DBL_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'DBL_MAX'
     */
    if (base != 0.0 && height > DBL_MAX / base) {
        return 0;
    }

    *area = base * height;
    return isfinite(*area);
}

static int parse_nonnegative_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(parsed) || parsed < 0.0) {
        return 0;
    }

    *value = parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    double base;
    double height;
    double area;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_nonnegative_double(argv[1], &base) ||
        !parse_nonnegative_double(argv[2], &height)) {
        fprintf(stderr, "Base and height must be finite, nonnegative numbers.\n");
        return EXIT_FAILURE;
    }

    if (!calculate_parallelogram_area(base, height, &area)) {
        fprintf(stderr, "Unable to calculate the area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}