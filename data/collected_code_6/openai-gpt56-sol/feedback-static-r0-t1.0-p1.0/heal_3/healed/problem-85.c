#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_surface_area(double radius, double *area)
{
    const double factor = 4.0 * 3.14159265358979323846;

    if (area == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    if (radius > sqrt(DBL_MAX / factor)) {
        return -1;
    }

    *area = factor * radius * radius;
    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    double radius;
    double area;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Invalid radius.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                fputs("Invalid radius.\n", stderr);
                return EXIT_FAILURE;
            }

            new_capacity = capacity == 0 ? 64 : capacity * 2;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                fputs("Failed to read the radius.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to read the radius.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || sphere_surface_area(radius, &area) != 0) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}