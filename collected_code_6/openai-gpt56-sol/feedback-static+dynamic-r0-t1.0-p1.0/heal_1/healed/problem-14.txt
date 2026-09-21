#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int triangular_prism_volume(double base, double height, double length,
                                   double *volume)
{
    double area;

    if (volume == NULL ||
        !isfinite(base) || !isfinite(height) || !isfinite(length) ||
        base < 0.0 || height < 0.0 || length < 0.0) {
        return 0;
    }

    area = 0.5 * base * height;
    if (!isfinite(area)) {
        return 0;
    }

    *volume = area * length;
    return isfinite(*volume);
}

static int read_positive_double(const char *prompt, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
    return 1;
}

int main(void)
{
    double base;
    double height;
    double length;
    double volume;

    if (!read_positive_double("Enter triangle base: ", &base) ||
        !read_positive_double("Enter triangle height: ", &height) ||
        !read_positive_double("Enter prism length: ", &length)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangular_prism_volume(base, height, length, &volume)) {
        fputs("Unable to calculate volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}