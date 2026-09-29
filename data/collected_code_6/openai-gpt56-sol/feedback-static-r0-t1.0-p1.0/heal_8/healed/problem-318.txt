#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int maximum_cuboid_volume(double side_sum, double *volume)
{
    double side;
    double limit;

    if (volume == NULL || !isfinite(side_sum) || side_sum < 0.0) {
        return -1;
    }

    side = side_sum / 3.0;
    limit = cbrt(DBL_MAX);

    if (!isfinite(side) || side > limit) {
        return -1;
    }

    *volume = side * side * side;

    return isfinite(*volume) ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    char *end;
    double side_sum;
    double volume;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to read the sum of sides.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read the sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to read the sum of sides.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    errno = 0;
    side_sum = strtod(input, &end);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || maximum_cuboid_volume(side_sum, &volume) != 0) {
        free(input);
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.17g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}