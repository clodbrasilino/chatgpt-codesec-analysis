#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

static int trapezium_median(double base1, double base2, double *median)
{
    if (median == NULL || !isfinite(base1) || !isfinite(base2) ||
        base1 <= 0.0 || base2 <= 0.0 || base1 > DBL_MAX - base2) {
        return -1;
    }

    *median = (base1 + base2) / 2.0;
    return 0;
}

static int read_positive_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end = NULL;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    fputs(prompt, stdout);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) || parsed <= 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (trapezium_median(base1, base2, &median) != 0) {
        fputs("Unable to calculate the median.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Median: %.6f\n", median);
    return EXIT_SUCCESS;
}