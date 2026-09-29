#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int read_positive_double(const char *name, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double parsed_value;

    if (name == NULL || value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read the %s diagonal.\n", name);
        free(line);
        return 0;
    }

    errno = 0;
    parsed_value = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        fprintf(stderr, "Invalid %s diagonal.\n", name);
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid %s diagonal.\n", name);
        free(line);
        return 0;
    }

    *value = parsed_value;
    free(line);
    return 1;
}

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    double half_diagonal;
    double result;

    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0;
    }

    half_diagonal = diagonal1 / 2.0;

    if (half_diagonal > DBL_MAX / diagonal2) {
        return 0;
    }

    result = half_diagonal * diagonal2;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (!read_positive_double("first", &diagonal1) ||
        !read_positive_double("second", &diagonal2)) {
        return EXIT_FAILURE;
    }

    if (!rhombus_area(diagonal1, diagonal2, &area)) {
        fputs("Unable to calculate a finite area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}