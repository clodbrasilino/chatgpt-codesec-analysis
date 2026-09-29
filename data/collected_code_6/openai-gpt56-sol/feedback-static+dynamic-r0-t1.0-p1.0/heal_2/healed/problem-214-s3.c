#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double radians_to_degrees(const double radians)
{
    return radians * (180.0 / acos(-1.0));
}

int main(const int argc, char *const argv[])
{
    const char *const program_name = argv[0];
    const char *const input = argc > 1 ? argv[1] : NULL;
    char *end = NULL;
    double radians;
    double degrees;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radians>\n", program_name);
        return EXIT_FAILURE;
    }

    errno = 0;
    radians = strtod(input, &end);

    if (end == input || *end != '\0' || errno == ERANGE ||
        !isfinite(radians)) {
        fprintf(stderr, "Invalid radians value: %s\n", input);
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