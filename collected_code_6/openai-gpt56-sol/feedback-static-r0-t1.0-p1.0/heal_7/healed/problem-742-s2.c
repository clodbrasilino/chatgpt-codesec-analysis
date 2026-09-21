#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_surface_area(double edge, double *area)
{
    const double root_three = 1.7320508075688772935;

    if (area == NULL || !isfinite(edge) || edge <= 0.0) {
        return 0;
    }

    if (edge > sqrt(DBL_MAX / root_three)) {
        return 0;
    }

    *area = root_three * edge * edge;
    return isfinite(*area);
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    char *end;
    double edge;
    double area;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_input;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read the edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        fputs("Failed to read the edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    edge = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0') {
        unsigned char c = (unsigned char)*end;

        if (c != ' ' && c != '\t' && c != '\r' &&
            c != '\v' && c != '\f') {
            free(input);
            fputs("Unexpected characters in input.\n", stderr);
            return EXIT_FAILURE;
        }

        ++end;
    }

    free(input);

    if (!tetrahedron_surface_area(edge, &area)) {
        fputs("Edge length must be a finite positive number within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}