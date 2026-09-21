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
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
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
    parsed = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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
    double radius;
    double height;
    double volume;

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