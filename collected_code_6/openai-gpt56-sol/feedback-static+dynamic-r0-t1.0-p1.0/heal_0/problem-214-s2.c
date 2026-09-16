#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double radians_to_degrees(double radians)
{
    return radians * (180.0 / acos(-1.0));
}

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

    if (errno == ERANGE || end == argv[1] || *end != '\0' || !isfinite(radians)) {
        fprintf(stderr, "Invalid radians value\n");
        return EXIT_FAILURE;
    }

    degrees = radians_to_degrees(radians);

    if (!isfinite(degrees)) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%.12g\n", degrees) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}