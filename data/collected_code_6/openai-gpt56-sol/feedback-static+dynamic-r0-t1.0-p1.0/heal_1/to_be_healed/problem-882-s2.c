#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int calculate_perimeter(double side_a, double side_b, double *perimeter)
{
    if (perimeter == NULL || !isfinite(side_a) || !isfinite(side_b) ||
        side_a <= 0.0 || side_b <= 0.0 ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'DBL_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'DBL_MAX'
         */
        side_a > DBL_MAX / 2.0 - side_b) {
        return 0;
    }

    *perimeter = 2.0 * (side_a + side_b);
    return isfinite(*perimeter);
}

static int read_positive_double(const char *prompt, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end = NULL;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    *value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(*value) || *value <= 0.0) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    return *end == '\0';
}

int main(void)
{
    double side_a;
    double side_b;
    double perimeter;

    if (!read_positive_double("Enter the first side length: ", &side_a) ||
        !read_positive_double("Enter the second side length: ", &side_b)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_perimeter(side_a, side_b, &perimeter)) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}