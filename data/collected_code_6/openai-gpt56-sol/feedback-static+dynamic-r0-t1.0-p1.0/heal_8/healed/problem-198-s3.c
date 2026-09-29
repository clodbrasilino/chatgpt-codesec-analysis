#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[3];
    double area;
} Triangle;

static int largest_inscribed_triangle(double semi_major, double semi_minor,
                                      Triangle *triangle)
{
    static const double angles[3] = {
        0.0,
        2.0943951023931954923,
        4.1887902047863909846
    };
    const double area_factor = 3.0 * sqrt(3.0) / 4.0;
    Triangle result;

    if (triangle == NULL ||
        !isfinite(semi_major) ||
        !isfinite(semi_minor) ||
        semi_major <= 0.0 ||
        semi_minor <= 0.0) {
        return 0;
    }

    for (size_t i = 0; i < 3; ++i) {
        if (fabs(cos(angles[i])) > DBL_MAX / semi_major ||
            fabs(sin(angles[i])) > DBL_MAX / semi_minor) {
            return 0;
        }

        result.vertices[i].x = semi_major * cos(angles[i]);
        result.vertices[i].y = semi_minor * sin(angles[i]);

        if (!isfinite(result.vertices[i].x) ||
            !isfinite(result.vertices[i].y)) {
            return 0;
        }
    }

    if (semi_major > DBL_MAX / area_factor / semi_minor) {
        return 0;
    }

    result.area = area_factor * semi_major * semi_minor;

    if (!isfinite(result.area)) {
        return 0;
    }

    *triangle = result;
    return 1;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*capacity > SIZE_MAX / 2) {
        return 0;
    }

    new_capacity = *capacity * 2;

    if (new_capacity <= *capacity) {
        return 0;
    }

    new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length >= capacity - 1) {
            if (!grow_buffer(&buffer, &capacity)) {
                free(buffer);
                return 0;
            }
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_positive_double(const char *prompt, double *value)
{
    char *buffer = NULL;
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(stdin, &buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    free(buffer);
    *value = parsed;
    return 1;
}

int main(void)
{
    double semi_major;
    double semi_minor;
    Triangle triangle;

    if (!read_positive_double("Enter the first semi-axis: ", &semi_major) ||
        !read_positive_double("Enter the second semi-axis: ", &semi_minor)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!largest_inscribed_triangle(semi_major, semi_minor, &triangle)) {
        fputs("Unable to compute the triangle.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum area: %.10g\n", triangle.area) < 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 3; ++i) {
        if (printf("Vertex %zu: (%.10g, %.10g)\n",
                   i + 1,
                   triangle.vertices[i].x,
                   triangle.vertices[i].y) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}