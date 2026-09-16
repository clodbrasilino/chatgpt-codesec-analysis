#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int radians_to_degrees(double radians, double *degrees)
{
    if (degrees == NULL || !isfinite(radians)) {
        return -1;
    }

    *degrees = radians * (180.0 / acos(-1.0));

    return isfinite(*degrees) ? 0 : -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
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

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        !isfinite(radians)) {
        fprintf(stderr, "Invalid radians value\n");
        return EXIT_FAILURE;
    }

    if (radians_to_degrees(radians, &degrees) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", degrees) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}