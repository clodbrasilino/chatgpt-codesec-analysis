#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int trapezium_median(double base1, double base2, double *median)
{
    if (median == NULL || !isfinite(base1) || !isfinite(base2) ||
        /* Possible weaknesses found:
         *  'DBL_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'DBL_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        base1 <= 0.0 || base2 <= 0.0 || base1 > DBL_MAX - base2) {
        return 0;
    }

    *median = base1 / 2.0 + base2 / 2.0;
    return isfinite(*median);
}

static int read_positive_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end = NULL;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    fputs(prompt, stdout);
    if (fflush(stdout) == EOF || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) || parsed <= 0.0) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
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

    printf("Median: %.10g\n", median);
    return EXIT_SUCCESS;
}