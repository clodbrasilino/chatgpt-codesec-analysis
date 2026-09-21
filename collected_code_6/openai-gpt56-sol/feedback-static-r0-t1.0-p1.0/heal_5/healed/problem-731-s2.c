#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_lateral_surface_area(double radius, double slant_height,
                                     double *area)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (area == NULL ||
        !isfinite(radius) ||
        !isfinite(slant_height) ||
        radius < 0.0 ||
        slant_height < 0.0) {
        return 0;
    }

    if (radius != 0.0 && slant_height > (DBL_MAX / pi) / radius) {
        return 0;
    }

    result = pi * radius * slant_height;
    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int discard_line_remainder(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    if (fgets(buffer, capacity, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < capacity && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (length == capacity) {
        return 0;
    }

    if (feof(stdin)) {
        return length != 0;
    }

    if (!discard_line_remainder()) {
        return 0;
    }

    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end;
    double parsed_value;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(buffer, sizeof buffer)) {
        return 0;
    }

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed_value;
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