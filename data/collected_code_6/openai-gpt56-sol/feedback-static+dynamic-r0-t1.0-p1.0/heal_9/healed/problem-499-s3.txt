#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL || !isfinite(radius) ||
        radius < 0.0 || radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = radius * 2.0;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_radius(double *radius)
{
    char *input = NULL;
    char *end;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    double value;

    if (radius == NULL) {
        return -1;
    }

    capacity = 64;
    input = malloc(capacity);
    if (input == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity > 4096 / 2) {
                free(input);

                if (discard_line() != 0) {
                    return -1;
                }

                return -2;
            }

            new_capacity = capacity * 2;
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

    input[length] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || !isfinite(value)) {
        free(input);
        return -1;
    }

    *radius = value;
    free(input);
    return 0;
}

int main(void)
{
    double radius;
    double diameter;
    int status;

    status = read_radius(&radius);

    if (status == -2) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0 || calculate_diameter(radius, &diameter) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", diameter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}