#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    const double pi = acos(-1.0);
    double value;

    if (result == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return -1;
    }

    value = 2.0 * (2.0 * pi * radius + height);
    if (!isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
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
        int ch = fgetc(stream);

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

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
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

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int parse_number(const char **input, double *value)
{
    const char *cursor;
    char *end;
    double parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return -1;
    }

    cursor = *input;
    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtod(cursor, &end);

    if (end == cursor || errno == ERANGE || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    *input = end;
    return 0;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    double radius;
    double height;
    double perimeter;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input) != 0) {
        return EXIT_FAILURE;
    }

    cursor = input;

    if (parse_number(&cursor, &radius) != 0 ||
        parse_number(&cursor, &height) != 0) {
        goto cleanup;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        goto cleanup;
    }

    if (cylinder_perimeter(radius, height, &perimeter) != 0) {
        goto cleanup;
    }

    if (printf("%.6f\n", perimeter) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}