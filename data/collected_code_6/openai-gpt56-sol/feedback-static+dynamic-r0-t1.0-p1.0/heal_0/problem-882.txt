#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_perimeter(double side_a, double side_b, double *perimeter)
{
    if (perimeter == NULL ||
        !isfinite(side_a) ||
        !isfinite(side_b) ||
        side_a <= 0.0 ||
        side_b <= 0.0 ||
        side_a > (DBL_MAX / 2.0) - side_b) {
        return 0;
    }

    *perimeter = 2.0 * (side_a + side_b);
    return 1;
}

static int parse_positive_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(int argc, char *argv[])
{
    double side_a;
    double side_b;
    double perimeter;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <side_a> <side_b>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_double(argv[1], &side_a) ||
        !parse_positive_double(argv[2], &side_b)) {
        fprintf(stderr, "Both sides must be finite positive numbers.\n");
        return EXIT_FAILURE;
    }

    if (!calculate_perimeter(side_a, side_b, &perimeter)) {
        fprintf(stderr, "Unable to calculate the perimeter.\n");
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.17g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}