#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int square_pyramid_surface_area(double base_side, double height,
                                       double *area)
{
    double half_side;
    double slant_height;
    double result;

    if (area == NULL || !isfinite(base_side) || !isfinite(height) ||
        base_side < 0.0 || height < 0.0) {
        return -1;
    }

    half_side = base_side / 2.0;
    slant_height = hypot(height, half_side);

    if (!isfinite(slant_height) ||
        (base_side != 0.0 && base_side > sqrt(DBL_MAX)) ||
        (base_side != 0.0 && slant_height > DBL_MAX / (2.0 * base_side))) {
        return -1;
    }

    result = base_side * base_side + 2.0 * base_side * slant_height;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    *line = NULL;
    *capacity = 0;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity = *capacity == 0 ? 128 : *capacity * 2;
            char *new_line;

            if (new_capacity <= *capacity) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return -1;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (length + 1 >= *capacity) {
        size_t new_capacity = length + 1;
        char *new_line = realloc(*line, new_capacity);

        if (new_line == NULL) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return -1;
        }

        *line = new_line;
        *capacity = new_capacity;
    }

    (*line)[length] = '\0';
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *buffer;
    char *end;
    size_t capacity;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (read_line(&buffer, &capacity) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        free(buffer);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = parsed;
    free(buffer);
    return 0;
}

int main(void)
{
    double base_side;
    double height;
    double area;

    if (read_nonnegative_double("Enter the base side length: ",
                                &base_side) != 0) {
        fputs("Invalid base side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the vertical height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (square_pyramid_surface_area(base_side, height, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}