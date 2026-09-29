#include <errno.h>
#include <float.h>
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
        base2 <= 0.0 ||
        base1 > DBL_MAX - base2) {
        return 0;
    }

    result = base1 / 2.0 + base2 / 2.0;
    if (!isfinite(result)) {
        return 0;
    }

    *median = result;
    return 1;
}

static int discard_remaining_input(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
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
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (buffer[0] == '\0') {
        return 0;
    }

    {
        size_t length = 0;

        while (buffer[length] != '\0') {
            ++length;
        }

        if (length > 0 && buffer[length - 1] != '\n' && !feof(stdin)) {
            discard_remaining_input();
            return 0;
        }
    }

    errno = 0;
    end = NULL;
    parsed = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed <= 0.0) {
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
        return 0;
    }

    *value = parsed;
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

    if (printf("Median: %.10g\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}