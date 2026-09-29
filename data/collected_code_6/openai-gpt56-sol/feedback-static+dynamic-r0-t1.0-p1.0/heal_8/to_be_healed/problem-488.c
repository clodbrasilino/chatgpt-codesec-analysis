#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int pentagon_area(double side, double *area)
{
    const double factor =
        sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) / 4.0;
    double result;

    if (area == NULL || !isfinite(side) || side <= 0.0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'DBL_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'DBL_MAX'
     */
    if (side > sqrt(DBL_MAX / factor)) {
        return -1;
    }

    result = factor * side * side;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    double side;
    double area;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(line, &end);

    if (end == line || errno == ERANGE) {
        free(line);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || pentagon_area(side, &area) != 0) {
        free(line);
        fputs("Side length must be a positive finite number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("%.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}