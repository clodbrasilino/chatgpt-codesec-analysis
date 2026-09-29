#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0 ||
        /* Possible weaknesses found:
         *  'DBL_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'DBL_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        diagonal1 > (2.0 * DBL_MAX) / diagonal2) {
        return -1;
    }

    *area = (diagonal1 * diagonal2) / 2.0;
    return isfinite(*area) ? 0 : -1;
}

static int read_positive_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end = NULL;
    double parsed_value;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed_value;
    return 0;
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (read_positive_double("Enter the first diagonal: ", &diagonal1) != 0 ||
        read_positive_double("Enter the second diagonal: ", &diagonal2) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (rhombus_area(diagonal1, diagonal2, &area) != 0) {
        fputs("Unable to calculate the area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Area of the rhombus: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}