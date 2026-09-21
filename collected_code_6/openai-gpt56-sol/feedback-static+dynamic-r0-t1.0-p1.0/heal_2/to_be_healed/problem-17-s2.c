#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int square_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL || !isfinite(side) || side < 0.0 ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'DBL_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'DBL_MAX'
         */
        side > DBL_MAX / 4.0) {
        return -1;
    }

    *perimeter = 4.0 * side;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    double side;
    double perimeter;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (errno == ERANGE || end == input || *end != '\0' || !isfinite(side)) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (square_perimeter(side, &perimeter) != 0) {
        fputs("Side length must be nonnegative and finite.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}