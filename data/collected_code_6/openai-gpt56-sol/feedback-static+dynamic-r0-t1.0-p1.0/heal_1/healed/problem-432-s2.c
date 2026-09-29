#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int trapezium_median(double base1, double base2, double *median)
{
    if (median == NULL ||
        !isfinite(base1) ||
        !isfinite(base2) ||
        base1 <= 0.0 ||
        base2 <= 0.0 ||
        base1 > DBL_MAX - base2) {
        return 0;
    }

    *median = base1 / 2.0 + base2 / 2.0;
    return isfinite(*median);
}

static int read_positive_double(const char *prompt, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    fputs(prompt, stdout);
    if (fflush(stdout) == EOF) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
        free(line);
        return 0;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\n' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
    return 1;
}

int main(void)
{
    double base1;
    double base2;
    double median;

    if (!read_positive_double("Enter the first base: ", &base1) ||
        !read_positive_double("Enter the second base: ", &base2)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!trapezium_median(base1, base2, &median)) {
        fputs("Unable to calculate the median.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Median: %.10g\n", median);
    return EXIT_SUCCESS;
}