#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_volume(double side, double *volume)
{
    double result;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    if (side > cbrt(DBL_MAX)) {
        return -1;
    }

    result = side * side * side;
    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double side;
    double volume;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0') {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input) {
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length > 0 && input[length - 1] != '\n' && !feof(stdin)) {
            ch = getchar();
            if (ch != '\n' && ch != EOF) {
                while ((ch = getchar()) != '\n' && ch != EOF) {
                }
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid trailing input.\n", stderr);
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