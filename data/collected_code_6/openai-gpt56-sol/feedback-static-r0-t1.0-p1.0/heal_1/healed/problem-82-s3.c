#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double sphere_volume(double radius)
{
    return (4.0 / 3.0) * acos(-1.0) * radius * radius * radius;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    ssize_t bytes_read;
    char *end = NULL;
    double radius;
    double volume;

    bytes_read = getline(&input, &length, stdin);
    if (bytes_read < 0) {
        fputs("Failed to read the radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius) || radius < 0.0) {
        fputs("Invalid radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    volume = sphere_volume(radius);
    free(input);

    if (!isfinite(volume)) {
        fputs("Volume is outside the representable range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}