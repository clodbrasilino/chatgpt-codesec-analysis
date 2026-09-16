#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int complex_angle(double real, double imaginary, double *angle)
{
    if (angle == NULL || !isfinite(real) || !isfinite(imaginary)) {
        return -1;
    }

    *angle = atan2(imaginary, real);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    double real;
    double imaginary;
    double angle;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <real> <imaginary>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    real = strtod(argv[1], &end);
    if (errno == ERANGE || end == argv[1] || *end != '\0' || !isfinite(real)) {
        fprintf(stderr, "Invalid real component\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    imaginary = strtod(argv[2], &end);
    if (errno == ERANGE || end == argv[2] || *end != '\0' ||
        !isfinite(imaginary)) {
        fprintf(stderr, "Invalid imaginary component\n");
        return EXIT_FAILURE;
    }

    if (complex_angle(real, imaginary, &angle) != 0) {
        fprintf(stderr, "Unable to calculate angle\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", angle);
    return EXIT_SUCCESS;
}