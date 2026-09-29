#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    const double pi = 3.14159265358979323846;

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    if (radius > DBL_MAX / (2.0 * pi)) {
        return -1;
    }

    *circumference = 2.0 * pi * radius;
    return 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input;
    char *end;
    double radius;
    double circumference;

    if (read_line(&input) != 0) {
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (calculate_circumference(radius, &circumference) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}