#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_lateral_surface_area(double radius, double slant_height,
                                     double *area)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (area == NULL || !isfinite(radius) || !isfinite(slant_height) ||
        radius < 0.0 || slant_height < 0.0) {
        return 0;
    }

    result = pi * radius * slant_height;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double parsed_value;

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
    parsed_value = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed_value;
    free(line);
    return 1;
}

int main(void)
{
    double radius;
    double slant_height;
    double area;

    if (!read_nonnegative_double("Enter the radius: ", &radius) ||
        !read_nonnegative_double("Enter the slant height: ", &slant_height)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cone_lateral_surface_area(radius, slant_height, &area)) {
        fputs("Unable to calculate the area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}