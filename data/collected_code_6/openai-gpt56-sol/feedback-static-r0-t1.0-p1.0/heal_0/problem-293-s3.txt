#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_third_side(double side1, double side2, double *third_side)
{
    if (third_side == NULL || !isfinite(side1) || !isfinite(side2) ||
        side1 <= 0.0 || side2 <= 0.0) {
        return -1;
    }

    *third_side = hypot(side1, side2);

    if (!isfinite(*third_side)) {
        return -1;
    }

    return 0;
}

static int parse_positive_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    *value = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' ||
        !isfinite(*value) || *value <= 0.0) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    double side1;
    double side2;
    double third_side;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <leg1> <leg2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_positive_double(argv[1], &side1) != 0 ||
        parse_positive_double(argv[2], &side2) != 0) {
        fputs("Error: both legs must be finite positive numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_third_side(side1, side2, &third_side) != 0) {
        fputs("Error: unable to calculate the hypotenuse.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.10g\n", third_side);
    return EXIT_SUCCESS;
}