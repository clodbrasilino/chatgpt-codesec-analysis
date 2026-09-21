#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double length, double width, double height,
                                double *area)
{
    double sum;
    double result;

    if (area == NULL ||
        !isfinite(length) ||
        !isfinite(width) ||
        !isfinite(height) ||
        length < 0.0 ||
        width < 0.0 ||
        height < 0.0) {
        return 0;
    }

    if (length > DBL_MAX - width) {
        return 0;
    }

    sum = length + width;

    if (height != 0.0 && sum > DBL_MAX / height / 2.0) {
        return 0;
    }

    result = 2.0 * height * sum;
    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    size_t length = 0;
    size_t capacity = 128;
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
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_dimension(const char *name, double *value)
{
    char *line = NULL;
    char *end;
    double parsed_value;
    int valid = 0;

    if (name == NULL || value == NULL) {
        return 0;
    }

    if (printf("Enter %s: ", name) < 0 || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(stdin, &line)) {
        return 0;
    }

    errno = 0;
    parsed_value = strtod(line, &end);

    if (end != line &&
        errno != ERANGE &&
        isfinite(parsed_value) &&
        parsed_value >= 0.0) {
        while (*end == ' ' ||
               *end == '\t' ||
               *end == '\r' ||
               *end == '\v' ||
               *end == '\f') {
            ++end;
        }

        if (*end == '\0') {
            *value = parsed_value;
            valid = 1;
        }
    }

    free(line);
    return valid;
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

    if (printf("Lateral surface area: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}