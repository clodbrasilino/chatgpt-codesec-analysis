#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double sphere_volume(double radius)
{
    const double pi = acos(-1.0);
    return (4.0 / 3.0) * pi * radius * radius * radius;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\0' && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    *end = '\0';

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius) || radius < 0.0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    volume = sphere_volume(radius);

    if (!isfinite(volume)) {
        fputs("Volume is outside the representable range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}