#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_inscribed_triangle(double radius, double *area)
{
    const double coefficient = 3.0 * sqrt(3.0) / 4.0;
    double maximum_radius;

    if (area == NULL || !isfinite(radius) || radius <= 0.0) {
        return -1;
    }

    maximum_radius = sqrt(DBL_MAX / coefficient);
    if (radius > maximum_radius) {
        return -1;
    }

    *area = coefficient * radius * radius;
    return isfinite(*area) ? 0 : -1;
}

static int read_line(FILE *stream, char **line)
{
    enum { INITIAL_CAPACITY = 64 };
    char *buffer;
    size_t capacity;
    size_t length;
    int ch;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    capacity = INITIAL_CAPACITY;
    length = 0;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -3;
    }

    while ((ch = fgetc(stream)) != EOF) {
        char *resized;
        size_t new_capacity;

        if (ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(buffer);
            return -2;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -2;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -3;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input;
    char *end;
    double radius;
    double area;
    int status;

    status = read_line(stdin, &input);
    if (status != 0) {
        if (status == -2) {
            fputs("Input is too long.\n", stderr);
        } else if (status == -3) {
            fputs("Failed to allocate memory.\n", stderr);
        } else {
            fputs("Failed to read the radius.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || largest_inscribed_triangle(radius, &area) != 0) {
        free(input);
        fputs("Radius must be a finite positive number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("Largest triangle area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}