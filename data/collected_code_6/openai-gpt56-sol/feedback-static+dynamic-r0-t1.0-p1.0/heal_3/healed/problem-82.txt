#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_volume(double radius, double *volume)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = (4.0 / 3.0) * pi * radius * radius * radius;

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
    double radius;
    double volume;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || sphere_volume(radius, &volume) != 0) {
        fputs("Invalid radius or volume out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}