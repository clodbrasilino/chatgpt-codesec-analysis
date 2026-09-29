#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    double result;

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = 2.0 * acos(-1.0) * radius;

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
    char *end;
    double radius;
    double circumference;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
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
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || radius < 0.0) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (calculate_circumference(radius, &circumference) != 0) {
        fputs("Unable to calculate the circumference.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}