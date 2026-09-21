#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_volume(double side, double *volume)
{
    double limit;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    limit = cbrt(DBL_MAX);
    if (side > limit) {
        return -1;
    }

    *volume = side * side * side;
    return isfinite(*volume) ? 0 : -1;
}

int main(void)
{
    char *line = NULL;
    char *end;
    size_t capacity = 0;
    ssize_t length;
    double side;
    double volume;

    errno = 0;
    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        fputs("Failed to read the cube's side length.\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        fputs("Invalid input.\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(line, &end);

    if (end == line || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    while (*end != '\0') {
        if (*end != ' ' && *end != '\t' && *end != '\r' &&
            *end != '\f' && *end != '\v') {
            fputs("Invalid trailing input.\n", stderr);
            free(line);
            return EXIT_FAILURE;
        }
        ++end;
    }

    free(line);

    if (cube_volume(side, &volume) != 0) {
        fputs("The side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}