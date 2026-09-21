#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_perimeter(double side_a, double side_b, double *perimeter)
{
    double sum;

    if (perimeter == NULL ||
        !isfinite(side_a) ||
        !isfinite(side_b) ||
        side_a <= 0.0 ||
        side_b <= 0.0 ||
        side_a > DBL_MAX - side_b) {
        return 0;
    }

    sum = side_a + side_b;

    if (sum > DBL_MAX / 2.0) {
        return 0;
    }

    *perimeter = 2.0 * sum;
    return isfinite(*perimeter);
}

static int discard_line_remainder(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch == '\n' || !ferror(stdin);
}

static int read_positive_double(const char *prompt, double *value)
{
    char *line;
    char *end;
    double parsed_value;
    size_t capacity;
    size_t length;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    capacity = 64;
    length = 0;
    line = malloc(capacity);

    if (line == NULL) {
        discard_line_remainder();
        return 0;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(line);
            discard_line_remainder();
            return 0;
        }

        if (length + 1 >= capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                discard_line_remainder();
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);

            if (resized == NULL) {
                free(line);
                discard_line_remainder();
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(line);
        return 0;
    }

    line[length] = '\0';

    errno = 0;
    parsed_value = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        free(line);
        return 0;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed_value;
    free(line);
    return 1;
}

int main(void)
{
    double side_a;
    double side_b;
    double perimeter;

    if (!read_positive_double("Enter the first side length: ", &side_a) ||
        !read_positive_double("Enter the second side length: ", &side_b)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_perimeter(side_a, side_b, &perimeter)) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}