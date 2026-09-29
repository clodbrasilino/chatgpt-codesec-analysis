#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = 2.0 * pi * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *circumference = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    char *new_input;
    double radius;
    double circumference;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;

        if (new_capacity <= length) {
            free(input);
            return EXIT_FAILURE;
        }

        new_input = realloc(input, new_capacity);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (calculate_circumference(radius, &circumference) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}