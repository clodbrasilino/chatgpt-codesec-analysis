#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_volume(double base_area, double height, double *volume)
{
    if (volume == NULL || !isfinite(base_area) || !isfinite(height) ||
        base_area < 0.0 || height < 0.0) {
        return -1;
    }

    *volume = (base_area * height) / 3.0;

    return isfinite(*volume) ? 0 : -1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end = NULL;
    double result;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    fputs(prompt, stdout);
    if (fflush(stdout) == EOF || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    result = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(result) || result < 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = result;
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