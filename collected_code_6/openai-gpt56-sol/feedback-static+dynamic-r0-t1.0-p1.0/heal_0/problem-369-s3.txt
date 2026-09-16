#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double length, double width, double height,
                                double *area)
{
    if (area == NULL || !isfinite(length) || !isfinite(width) ||
        !isfinite(height) || length < 0.0 || width < 0.0 || height < 0.0) {
        return 0;
    }

    *area = 2.0 * height * (length + width);
    return isfinite(*area);
}

static int read_dimension(const char *name, double *value)
{
    char input[256];
    char *end = NULL;

    if (name == NULL || value == NULL) {
        return 0;
    }

    printf("Enter %s: ", name);
    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    *value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(*value) || *value < 0.0) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    return *end == '\n' || *end == '\0';
}

int main(void)
{
    double length;
    double width;
    double height;
    double area;

    if (!read_dimension("length", &length) ||
        !read_dimension("width", &width) ||
        !read_dimension("height", &height)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(length, width, height, &area)) {
        fputs("Unable to calculate the lateral surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Lateral surface area: %.2f\n", area);
    return EXIT_SUCCESS;
}