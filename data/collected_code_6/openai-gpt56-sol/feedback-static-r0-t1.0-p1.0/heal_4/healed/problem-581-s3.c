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

    if (base_side != 0.0 && base_side > DBL_MAX / base_side) {
        return -1;
    }

    base_area = base_side * base_side;

    if (base_side != 0.0 && slant_height > DBL_MAX / base_side) {
        return -1;
    }

    lateral_area = base_side * slant_height;

    if (lateral_area > DBL_MAX / 2.0) {
        return -1;
    }

    lateral_area *= 2.0;

    if (base_area > DBL_MAX - lateral_area) {
        return -1;
    }

    *area = base_area + lateral_area;
    return isfinite(*area) ? 0 : -1;
}

static int read_line(char **line, size_t *capacity)
{
    char *buffer;
    size_t length = 0;
    size_t allocated = 128;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    *line = NULL;
    *capacity = 0;

    buffer = malloc(allocated);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
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

        if (length + 1 >= allocated) {
            size_t new_capacity;
            char *new_buffer;

            if (allocated > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = allocated * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            allocated = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    *capacity = allocated;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *buffer = NULL;
    char *end;
    size_t capacity = 0;
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