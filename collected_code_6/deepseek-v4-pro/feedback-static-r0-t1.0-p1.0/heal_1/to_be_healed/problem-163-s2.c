#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

double regular_polygon_area(unsigned int n, double side_length)
{
    if (n < 3 || side_length <= 0.0) {
        errno = EINVAL;
        return -1.0;
    }

    /* Possible weaknesses found:
     *  'DBL_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'DBL_MAX'
     */
    if (side_length > (DBL_MAX / (4.0 * tan(M_PI / n)))) {
        errno = ERANGE;
        return -1.0;
    }

    double area = (n * side_length * side_length) / (4.0 * tan(M_PI / n));
    return area;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <sides> <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long sides = strtoul(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     */
    if (errno != 0 || *endptr != '\0' || sides > UINT_MAX) {
        fprintf(stderr, "Invalid number of sides\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double side_len = strtod(argv[2], &endptr);
    if (errno != 0 || *endptr != '\0') {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double area = regular_polygon_area((unsigned int)sides, side_len);
    if (errno != 0) {
        perror("Error calculating polygon area");
        return EXIT_FAILURE;
    }

    printf("%.15f\n", area);
    return EXIT_SUCCESS;
}