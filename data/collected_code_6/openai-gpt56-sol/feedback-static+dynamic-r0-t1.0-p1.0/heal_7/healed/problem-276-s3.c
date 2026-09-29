#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int cylinder_volume(double radius, double height, double *volume)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return -1;
    }

    result = pi * radius * radius * height;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    ssize_t length;
    double result;
    int status = -1;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        goto cleanup;
    }

    errno = 0;
    result = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(result) ||
        result < 0.0) {
        goto cleanup;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\n' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = result;
    status = 0;

cleanup:
    free(line);
    return status;
}

int main(void)
{
    double radius;
    double height;
    double volume;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cylinder_volume(radius, height, &volume) != 0) {
        fputs("Unable to calculate the volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}