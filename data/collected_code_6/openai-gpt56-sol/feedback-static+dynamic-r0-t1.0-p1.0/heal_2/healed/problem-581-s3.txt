#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int square_pyramid_surface_area(double base_side, double height,
                                       double *area)
{
    double half_side;
    double slant_height;
    double base_area;
    double lateral_area;

    if (area == NULL || !isfinite(base_side) || !isfinite(height) ||
        base_side < 0.0 || height < 0.0) {
        return -1;
    }

    half_side = base_side / 2.0;
    slant_height = hypot(height, half_side);

    if (!isfinite(slant_height)) {
        return -1;
    }

    if (base_side != 0.0 &&
        (base_side > DBL_MAX / base_side ||
         slant_height > DBL_MAX / base_side)) {
        return -1;
    }

    base_area = base_side * base_side;
    lateral_area = base_side * slant_height;

    if (!isfinite(base_area) || !isfinite(lateral_area) ||
        lateral_area > (DBL_MAX - base_area) / 2.0) {
        return -1;
    }

    *area = base_area + 2.0 * lateral_area;
    return isfinite(*area) ? 0 : -1;
}

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *line;
    char *end;
    double parsed;
    size_t capacity = 128;
    size_t length = 0;
    int ch;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(line);
            discard_line();
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                discard_line();
                return -1;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                discard_line();
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return -1;
    }

    line[length] = '\0';

    errno = 0;
    parsed = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        free(line);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = parsed;
    free(line);
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