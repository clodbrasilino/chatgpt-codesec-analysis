#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_surface_area(double radius, double *area)
{
    const double factor = 4.0 * 3.14159265358979323846;
    const double maximum_radius = sqrt(DBL_MAX / factor);

    if (area == NULL || !isfinite(radius) || radius < 0.0 ||
        radius > maximum_radius) {
        return -1;
    }

    *area = factor * radius * radius;
    return isfinite(*area) ? 0 : -1;
}

static int discard_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_radius(double *radius)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    double value;

    if (radius == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    if (discard_line() != 0) {
                        return -1;
                    }
                    return 1;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                if (discard_line() != 0) {
                    return -1;
                }
                return -1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return -1;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return -1;
    }

    if (length + 1 >= capacity) {
        char *resized;

        if (length == SIZE_MAX) {
            free(input);
            return -1;
        }

        resized = realloc(input, length + 1);
        if (resized == NULL) {
            free(input);
            return -1;
        }

        input = resized;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return 1;
    }

    *radius = value;
    free(input);
    return 0;
}

int main(void)
{
    double radius;
    double area;
    int result;

    result = read_radius(&radius);
    if (result != 0) {
        fputs(result < 0 ? "Failed to read the radius.\n"
                         : "Invalid radius.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (sphere_surface_area(radius, &area) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}