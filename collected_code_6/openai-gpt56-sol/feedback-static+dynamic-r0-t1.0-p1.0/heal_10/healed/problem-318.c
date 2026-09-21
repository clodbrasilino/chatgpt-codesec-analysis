#include <errno.h>
#include <float.h>
#include <math.h>
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

static int discard_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch;
}

static int read_side_sum(double *side_sum)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    int ch;
    double value;

    if (side_sum == NULL) {
        return -1;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(input);
                    discard_line();
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                discard_line();
                return -1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(input);
        return -1;
    }

    if (length == capacity) {
        size_t new_capacity;
        char *new_input;

        if (capacity == (size_t)-1) {
            free(input);
            return -1;
        }

        new_capacity = capacity == 0 ? 1 : capacity + 1;
        new_input = realloc(input, new_capacity);
        if (new_input == NULL) {
            free(input);
            return -1;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(value)) {
        free(input);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return -1;
    }

    *side_sum = value;
    free(input);
    return 0;
}

int main(void)
{
    double side_sum;
    double volume;

    if (read_side_sum(&side_sum) != 0 ||
        maximum_cuboid_volume(side_sum, &volume) != 0) {
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}