#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <string.h>

static int trapezium_median(double base1, double base2, double *median)
{
    if (median == NULL ||
        !isfinite(base1) ||
        !isfinite(base2) ||
        base1 <= 0.0 ||
        base2 <= 0.0 ||
        base1 > DBL_MAX - base2) {
        return -1;
    }

    *median = base1 / 2.0 + base2 / 2.0;
    return 0;
}

static int read_positive_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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

    if (printf("Median: %.6f\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}