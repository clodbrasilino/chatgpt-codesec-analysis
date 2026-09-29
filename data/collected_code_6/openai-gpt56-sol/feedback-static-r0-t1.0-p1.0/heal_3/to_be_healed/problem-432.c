#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

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

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
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

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
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