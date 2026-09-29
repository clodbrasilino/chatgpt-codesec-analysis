#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_surface_area(double radius, double height, double *area)
{
    const double pi = acos(-1.0);
    double sum;
    double factor;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    if (radius > DBL_MAX - height) {
        return -1;
    }

    sum = radius + height;

    if (radius != 0.0 && sum > DBL_MAX / radius) {
        return -1;
    }

    factor = radius * sum;

    if (factor > DBL_MAX / (2.0 * pi)) {
        return -1;
    }

    *area = 2.0 * pi * factor;
    return isfinite(*area) ? 0 : -1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int parse_values(const char *input, double *radius, double *height)
{
    char *end;

    if (input == NULL || radius == NULL || height == NULL) {
        return -1;
    }

    while (*input != '\0' && isspace((unsigned char)*input)) {
        ++input;
    }

    errno = 0;
    *radius = strtod(input, &end);
    if (end == input || errno == ERANGE || !isfinite(*radius)) {
        return -1;
    }

    input = end;
    errno = 0;
    *height = strtod(input, &end);
    if (end == input || errno == ERANGE || !isfinite(*height)) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0' ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    double radius;
    double height;
    double area;

    if (fputs("Enter radius and height: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write prompt.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_line(&input) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_values(input, &radius, &height) != 0) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (cylinder_surface_area(radius, height, &area) != 0) {
        fputs("Unable to calculate surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}