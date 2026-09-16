#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double degrees_to_radians(double degrees)
{
    const double pi = 3.14159265358979323846;

    return degrees * (pi / 180.0);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    double degrees;
    double radians;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    degrees = strtod(argv[1], &end);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        !isfinite(degrees)) {
        fprintf(stderr, "Invalid degree value: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    if (!isfinite(radians)) {
        fputs("Conversion produced a non-finite result.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", radians) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}