#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int triangular_prism_volume(double base, double height, double length,
                                   double *volume)
{
    if (volume == NULL || !isfinite(base) || !isfinite(height) ||
        !isfinite(length) || base < 0.0 || height < 0.0 || length < 0.0) {
        return 0;
    }

    *volume = 0.5 * base * height * length;
    return isfinite(*volume);
}

static int read_positive_number(const char *prompt, double *value)
{
    char buffer[256];
    char *end;

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
    double base;
    double height;
    double length;
    double volume;

    if (!read_positive_number("Triangle base: ", &base) ||
        !read_positive_number("Triangle height: ", &height) ||
        !read_positive_number("Prism length: ", &length)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangular_prism_volume(base, height, length, &volume)) {
        fputs("Unable to calculate a finite volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}