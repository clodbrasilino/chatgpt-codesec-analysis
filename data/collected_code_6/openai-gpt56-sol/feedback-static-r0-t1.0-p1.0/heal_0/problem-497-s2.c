#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_surface_area(double radius, double height, double *area)
{
    double slant_height;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    slant_height = hypot(radius, height);
    *area = acos(-1.0) * radius * (radius + slant_height);

    return isfinite(*area) ? 0 : -1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    *value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(*value) || *value < 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    return *end == '\0' ? 0 : -1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0 ||
        read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cone_surface_area(radius, height, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}