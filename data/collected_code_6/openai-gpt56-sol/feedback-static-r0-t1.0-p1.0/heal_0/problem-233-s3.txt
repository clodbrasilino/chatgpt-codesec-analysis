#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double radius, double height, double *area)
{
    const double pi = 3.14159265358979323846;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return 0;
    }

    *area = 2.0 * pi * radius * height;
    return isfinite(*area);
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end = NULL;
    double parsed;

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
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (!read_nonnegative_double("Enter the radius: ", &radius) ||
        !read_nonnegative_double("Enter the height: ", &height)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(radius, height, &area)) {
        fputs("Unable to calculate the lateral surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}