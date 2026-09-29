#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_surface_area(double radius, double *area)
{
    const double factor = 4.0 * 3.14159265358979323846;
    const double max_radius = sqrt(DBL_MAX / factor);

    if (area == NULL || !isfinite(radius) || radius < 0.0 ||
        radius > max_radius) {
        return -1;
    }

    *area = factor * radius * radius;
    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 64;
    int ch;
    char *end;
    double radius;
    double area;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_input;

            if (capacity > 4096 / 2) {
                fputs("Input is too long.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read the radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        fputs("Failed to read the radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (sphere_surface_area(radius, &area) != 0) {
        fputs("Radius must be a finite, nonnegative value within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}