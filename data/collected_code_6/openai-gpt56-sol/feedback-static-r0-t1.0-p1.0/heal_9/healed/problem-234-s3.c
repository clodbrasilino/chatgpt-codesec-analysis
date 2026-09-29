#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_volume(double side, double *volume)
{
    double limit;
    double result;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    limit = cbrt(DBL_MAX);
    if (side > limit) {
        return -1;
    }

    result = side * side * side;
    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static int read_side(double *side)
{
    double value;
    int ch;

    if (side == NULL) {
        return -1;
    }

    errno = 0;

    if (scanf(" %lf", &value) != 1) {
        return feof(stdin) ? -1 : 2;
    }

    if (errno == ERANGE) {
        return 2;
    }

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF && isspace((unsigned char)ch));

    if (ch != '\n' && ch != EOF) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 2;
    }

    *side = value;
    return 0;
}

int main(void)
{
    double side;
    double volume;
    int status;

    status = read_side(&side);

    if (status < 0) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_volume(side, &volume) != 0) {
        fputs("The side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}