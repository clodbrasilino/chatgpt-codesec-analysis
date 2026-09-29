#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

static int parse_double(const char **input, double *value)
{
    char *end;

    if (input == NULL || *input == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0') {
        return -1;
    }

    errno = 0;
    *value = strtod(*input, &end);

    if (end == *input || errno == ERANGE || !isfinite(*value)) {
        return -1;
    }

    *input = end;
    return 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
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

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *buffer = NULL;
    const char *input;
    double radius;
    double height;
    double perimeter;
    int status = EXIT_FAILURE;

    if (read_line(&buffer) != 0) {
        goto cleanup;
    }

    input = buffer;

    if (parse_double(&input, &radius) != 0 ||
        parse_double(&input, &height) != 0) {
        goto cleanup;
    }

    while (isspace((unsigned char)*input)) {
        ++input;
    }

    if (*input != '\0') {
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
    free(buffer);
    return status;
}