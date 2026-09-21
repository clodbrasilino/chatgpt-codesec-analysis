#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int triangular_prism_volume(double base, double height, double length,
                                   double *volume)
{
    double result;

    if (volume == NULL ||
        !isfinite(base) || !isfinite(height) || !isfinite(length) ||
        base < 0.0 || height < 0.0 || length < 0.0) {
        return 0;
    }

    result = 0.5 * base * height * length;

    if (!isfinite(result)) {
        return 0;
    }

    *volume = result;
    return 1;
}

static int read_positive_number(const char *prompt, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_line;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return 0;
    }

    if (length + 1 >= capacity) {
        char *new_line;
        size_t new_capacity = length + 1;

        new_line = realloc(line, new_capacity);
        if (new_line == NULL) {
            free(line);
            return 0;
        }

        line = new_line;
        capacity = new_capacity;
    }

    line[length] = '\0';

    errno = 0;
    *value = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(*value) || *value < 0.0) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    free(line);
    return 1;
}

int main(void)
{
    double base;
    double height;
    double length;
    double volume;

    if (!read_positive_number("Triangle base: ", &base) ||
        !read_positive_number("Triangle height: ", &height) ||
        !read_positive_number("Prism length: ", &length)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangular_prism_volume(base, height, length, &volume)) {
        fputs("Unable to calculate a finite volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}