#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_volume(double base_area, double height, double *volume)
{
    double result;

    if (volume == NULL || !isfinite(base_area) || !isfinite(height) ||
        base_area < 0.0 || height < 0.0) {
        return -1;
    }

    result = (base_area / 3.0) * height;
    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double result;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    errno = 0;
    end = NULL;
    result = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(result) || result < 0.0) {
        free(line);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = result;
    free(line);
    return 0;
}

int main(void)
{
    double base_area;
    double height;
    double volume;

    if (read_nonnegative_double("Enter the base area: ", &base_area) != 0) {
        fputs("Invalid base area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (tetrahedron_volume(base_area, height, &volume) != 0) {
        fputs("Unable to calculate the volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}