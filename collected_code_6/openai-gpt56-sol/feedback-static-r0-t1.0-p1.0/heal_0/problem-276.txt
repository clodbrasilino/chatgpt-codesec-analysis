#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double cylinder_volume(double radius, double height)
{
    const double pi = acos(-1.0);
    return pi * radius * radius * height;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end = NULL;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    *value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(*value) || *value < 0.0) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    return *end == '\0';
}

int main(void)
{
    double radius = 0.0;
    double height = 0.0;
    double volume = 0.0;

    if (!read_nonnegative_double("Enter the radius: ", &radius)) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_nonnegative_double("Enter the height: ", &height)) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    volume = cylinder_volume(radius, height);

    if (!isfinite(volume)) {
        fputs("The calculated volume is out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}