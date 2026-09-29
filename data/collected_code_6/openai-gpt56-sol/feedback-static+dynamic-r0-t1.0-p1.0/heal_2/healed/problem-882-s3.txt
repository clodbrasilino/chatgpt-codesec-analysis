#include <errno.h>
#include <float.h>
#include <math.h>
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

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > ((size_t)-1) / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_positive_double(const char *prompt, double *value)
{
    char *buffer;
    char *end;
    double parsed_value;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        free(buffer);
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
        free(buffer);
        return 0;
    }

    *value = parsed_value;
    free(buffer);
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

    if (printf("Perimeter: %.10g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}