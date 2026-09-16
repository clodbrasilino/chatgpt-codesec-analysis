#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int degrees_to_radians(double degrees, double *radians)
{
    const double pi = 3.14159265358979323846;

    if (radians == NULL || !isfinite(degrees)) {
        return -1;
    }

    *radians = degrees * pi / 180.0;

    return isfinite(*radians) ? 0 : -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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

    if (errno == ERANGE || end == argv[1] || *end != '\0' || !isfinite(degrees)) {
        fprintf(stderr, "Invalid degree value\n");
        return EXIT_FAILURE;
    }

    if (degrees_to_radians(degrees, &radians) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", radians) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}