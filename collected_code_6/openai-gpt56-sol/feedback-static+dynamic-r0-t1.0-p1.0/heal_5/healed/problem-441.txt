#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 64U
#define MAX_INPUT_LENGTH 4095U

static int cube_surface_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    if (side > sqrt(DBL_MAX / 6.0)) {
        return -1;
    }

    *area = 6.0 * side * side;
    return 0;
}

int main(void)
{
    char *input = malloc(INITIAL_CAPACITY);
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;
    char *end;
    double side;
    double area;
    int ch;

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= MAX_INPUT_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(input);

            if (ferror(stdin)) {
                fputs("Failed to read the side length.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > (MAX_INPUT_LENGTH + 1U) / 2U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            } else {
                new_capacity = capacity * 2U;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid trailing input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (cube_surface_area(side, &area) != 0) {
        fputs("Side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}