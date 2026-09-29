#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int discard_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_positive_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
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
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(void)
{
    double base1;
    double base2;
    double median;

    if (read_positive_double("Enter the first parallel side: ", &base1) != 0 ||
        read_positive_double("Enter the second parallel side: ", &base2) != 0) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (trapezium_median(base1, base2, &median) != 0) {
        if (fputs("Unable to calculate the median.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Median: %.10g\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}