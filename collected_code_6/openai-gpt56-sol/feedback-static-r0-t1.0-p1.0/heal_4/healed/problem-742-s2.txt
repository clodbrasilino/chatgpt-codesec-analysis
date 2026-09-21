#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int tetrahedron_surface_area(double edge, double *area)
{
    const double root_three = sqrt(3.0);
    double result;

    if (area == NULL || !isfinite(edge) || edge <= 0.0) {
        return 0;
    }

    if (edge > sqrt(DBL_MAX / root_three)) {
        return 0;
    }

    result = root_three * edge * edge;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    double edge;
    double area;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *temporary;

        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

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

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                fputs("Unable to allocate input buffer.\n", stderr);
                return EXIT_FAILURE;
            }

            input = temporary;
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

    if (capacity <= length) {
        char *temporary;

        temporary = realloc(input, length + 1);
        if (temporary == NULL) {
            free(input);
            fputs("Unable to allocate input buffer.\n", stderr);
            return EXIT_FAILURE;
        }

        input = temporary;
    }

    input[length] = '\0';

    errno = 0;
    edge = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Unexpected characters in input.\n", stderr);
        return EXIT_FAILURE;
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