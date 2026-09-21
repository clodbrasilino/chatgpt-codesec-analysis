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

    if (height > DBL_MAX / 2.0 ||
        (height != 0.0 && sum > DBL_MAX / (2.0 * height))) {
        return 0;
    }

    *area = 2.0 * height * sum;
    return isfinite(*area);
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    *line = NULL;
    *capacity = 128;

    *line = malloc(*capacity);
    if (*line == NULL) {
        *capacity = 0;
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return 0;
            }
            break;
        }

        if (length >= *capacity - 1) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return 0;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);

            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    (*line)[length] = '\0';
    return 1;
}

static int read_dimension(const char *name, double *value)
{
    char *line = NULL;
    char *end;
    size_t capacity = 0;
    double parsed_value;
    int result = 0;

    if (name == NULL || value == NULL) {
        return 0;
    }

    if (printf("Enter %s: ", name) < 0 || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(&line, &capacity)) {
        return 0;
    }

    errno = 0;
    parsed_value = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        goto cleanup;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\r' ||
           *end == '\v' ||
           *end == '\f') {
        ++end;
    }

    if (*end == '\0') {
        *value = parsed_value;
        result = 1;
    }

cleanup:
    free(line);
    return result;
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