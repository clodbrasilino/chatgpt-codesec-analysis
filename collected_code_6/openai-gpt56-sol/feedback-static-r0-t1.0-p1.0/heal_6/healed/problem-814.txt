#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
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

static int read_positive_double(const char *name, double *value)
{
    char *buffer = NULL;
    char *end;
    double parsed_value;

    if (name == NULL || value == NULL) {
        return 0;
    }

    if (!read_line(&buffer)) {
        fprintf(stderr, "Failed to read the %s diagonal.\n", name);
        return 0;
    }

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        fprintf(stderr, "Invalid %s diagonal.\n", name);
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid %s diagonal.\n", name);
        free(buffer);
        return 0;
    }

    free(buffer);
    *value = parsed_value;
    return 1;
}

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    double result;

    if (area == NULL ||
        !isfinite(diagonal1) ||
        !isfinite(diagonal2) ||
        diagonal1 <= 0.0 ||
        diagonal2 <= 0.0) {
        return 0;
    }

    if (diagonal1 / 2.0 > DBL_MAX / diagonal2) {
        return 0;
    }

    result = (diagonal1 / 2.0) * diagonal2;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (!read_positive_double("first", &diagonal1) ||
        !read_positive_double("second", &diagonal2)) {
        return EXIT_FAILURE;
    }

    if (!rhombus_area(diagonal1, diagonal2, &area)) {
        fputs("Unable to calculate a finite area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}