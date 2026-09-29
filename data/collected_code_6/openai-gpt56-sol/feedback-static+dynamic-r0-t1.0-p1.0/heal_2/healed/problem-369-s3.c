#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double length, double width, double height,
                                double *area)
{
    double perimeter;
    double result;

    if (area == NULL ||
        !isfinite(length) || !isfinite(width) || !isfinite(height) ||
        length < 0.0 || width < 0.0 || height < 0.0) {
        return 0;
    }

    perimeter = length + width;
    if (!isfinite(perimeter)) {
        return 0;
    }

    result = 2.0 * height * perimeter;
    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int read_dimension(const char *name, double *value)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double parsed;

    if (name == NULL || value == NULL) {
        return 0;
    }

    printf("Enter %s: ", name);
    if (fflush(stdout) == EOF) {
        return 0;
    }

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return 0;
    }

    errno = 0;
    parsed = strtod(input, &end);

    if (end == input || errno == ERANGE ||
        !isfinite(parsed) || parsed < 0.0) {
        free(input);
        return 0;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return 0;
    }

    *value = parsed;
    free(input);
    return 1;
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