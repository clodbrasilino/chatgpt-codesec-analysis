#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double radians_to_degrees(double radians)
{
    return radians * (180.0 / acos(-1.0));
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    double radians;
    double degrees;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radians>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    radians = strtod(argv[1], &end);

    if (end == argv[1] || *end != '\0' || errno == ERANGE || !isfinite(radians)) {
        fprintf(stderr, "Invalid radians value: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    degrees = radians_to_degrees(radians);

    if (!isfinite(degrees)) {
        fputs("Conversion produced a non-finite result.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", degrees) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}