#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_surface_area(double radius, double *area)
{
    const double pi = 3.14159265358979323846;
    const double maximum_radius = sqrt(DBL_MAX / pi);

    if (area == NULL || !isfinite(radius) || radius < 0.0 ||
        radius > maximum_radius) {
        return -1;
    }

    *area = pi * radius * radius;

    return isfinite(*area) ? 0 : -1;
}

static int read_line(FILE *stream, char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length == 0 && feof(stream)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;

    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    double radius;
    double area;
    int read_status;

    if (fputs("Enter the cylinder radius: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write the prompt.\n", stderr);
        return EXIT_FAILURE;
    }

    read_status = read_line(stdin, &input);

    if (read_status <= 0) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (radius < 0.0) {
        fputs("Radius must be a non-negative number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_surface_area(radius, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Top or bottom surface area: %.10g\n", area) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}