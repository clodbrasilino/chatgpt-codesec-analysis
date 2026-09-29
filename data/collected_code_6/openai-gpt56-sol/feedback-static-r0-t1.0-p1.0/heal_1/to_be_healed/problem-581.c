#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int square_pyramid_surface_area(double base_side, double slant_height,
                                       double *area)
{
    if (area == NULL || !isfinite(base_side) || !isfinite(slant_height) ||
        base_side < 0.0 || slant_height < 0.0) {
        return -1;
    }

    *area = base_side * base_side + 2.0 * base_side * slant_height;

    if (!isfinite(*area)) {
        return -1;
    }

    return 0;
}

static int parse_nonnegative_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    *value = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(*value) || *value < 0.0) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    double base_side;
    double slant_height;
    double area;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base-side> <slant-height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_nonnegative_double(argv[1], &base_side) != 0 ||
        parse_nonnegative_double(argv[2], &slant_height) != 0) {
        fprintf(stderr, "Error: dimensions must be finite, nonnegative numbers.\n");
        return EXIT_FAILURE;
    }

    if (square_pyramid_surface_area(base_side, slant_height, &area) != 0) {
        fprintf(stderr, "Error: unable to calculate a finite surface area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}