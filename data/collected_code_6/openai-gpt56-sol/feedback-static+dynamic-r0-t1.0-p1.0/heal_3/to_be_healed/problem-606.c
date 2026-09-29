#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double degrees_to_radians(double degrees)
{
    return degrees * (acos(-1.0) / 180.0);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *const *args = (const char *const *)argv;
    char *end = NULL;
    double degrees;
    double radians;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <degrees>\n", args[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    degrees = strtod(args[1], &end);

    if (errno == ERANGE || end == args[1] || *end != '\0' || !isfinite(degrees)) {
        fprintf(stderr, "Invalid degree value: %s\n", args[1]);
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    if (!isfinite(radians)) {
        fputs("Conversion produced a non-finite result.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", radians) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}