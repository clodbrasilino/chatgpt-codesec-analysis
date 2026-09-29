#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double radius, double height, double *area)
{
    double result;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return 0;
    }

    result = 2.0 * acos(-1.0) * radius * height;
    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int read_double(const char *prompt, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double result;

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

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    errno = 0;
    result = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(result)) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = result;
    free(line);
    return 1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (!read_double("Enter the radius: ", &radius) ||
        !read_double("Enter the height: ", &height)) {
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