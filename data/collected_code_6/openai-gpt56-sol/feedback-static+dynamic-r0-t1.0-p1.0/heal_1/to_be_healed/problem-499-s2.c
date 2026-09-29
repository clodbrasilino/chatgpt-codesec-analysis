#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int calculate_diameter(double radius, double *diameter)
{
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'DBL_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'DBL_MAX'
     */
    if (diameter == NULL || !isfinite(radius) || radius < 0.0 || radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = 2.0 * radius;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end = NULL;
    double radius;
    double diameter;

    printf("Enter the radius: ");
    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || calculate_diameter(radius, &diameter) != 0) {
        fprintf(stderr, "Radius must be a finite, nonnegative number in range.\n");
        return EXIT_FAILURE;
    }

    printf("Diameter: %.10g\n", diameter);
    return EXIT_SUCCESS;
}