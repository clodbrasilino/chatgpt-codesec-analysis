#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int trapezium_median(double base1, double base2, double *median)
{
    double result;

    if (median == NULL ||
        !isfinite(base1) ||
        !isfinite(base2) ||
        base1 <= 0.0 ||
        base2 <= 0.0) {
        return -1;
    }

    result = base1 / 2.0 + base2 / 2.0;
    if (!isfinite(result)) {
        return -1;
    }

    *median = result;
    return 0;
}

static int read_positive_double(const char *prompt, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
        free(line);
        return -1;
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
        return -1;
    }

    *value = parsed;
    free(line);
    return 0;
}

int main(void)
{
    double base1;
    double base2;
    double median;

    if (read_positive_double("Enter the first parallel side: ", &base1) != 0 ||
        read_positive_double("Enter the second parallel side: ", &base2) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (trapezium_median(base1, base2, &median) != 0) {
        fputs("Unable to calculate the median.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Median: %.10g\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}