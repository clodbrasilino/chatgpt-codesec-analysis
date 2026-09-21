#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_lateral_surface_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side < 0.0 ||
        side > sqrt(DBL_MAX / 4.0)) {
        return -1;
    }

    *area = 4.0 * side * side;
    return 0;
}

static int read_line(char **buffer)
{
    size_t capacity = 128;
    size_t length = 0;
    char *line;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    line = malloc(capacity);
    if (line == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return -1;
            }
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return -1;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    line[length] = '\0';
    *buffer = line;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    double side;
    double area;

    if (read_line(&input) != 0) {
        fputs("Failed to read the cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || cube_lateral_surface_area(side, &area) != 0) {
        free(input);
        fputs("Invalid cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}