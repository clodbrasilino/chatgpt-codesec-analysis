#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int calculate_perimeter(size_t sides, double side_length, double *perimeter)
{
    if (perimeter == NULL || sides < 3 || !isfinite(side_length) ||
        /* Possible weaknesses found:
         *  'DBL_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'DBL_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        side_length <= 0.0 || (double)sides > DBL_MAX / side_length) {
        return 0;
    }

    *perimeter = (double)sides * side_length;
    return isfinite(*perimeter);
}

int main(void)
{
    size_t sides = 0;
    double side_length = 0.0;
    double perimeter = 0.0;

    if (scanf("%zu %lf", &sides, &side_length) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!calculate_perimeter(sides, side_length, &perimeter)) {
        fprintf(stderr, "Invalid polygon dimensions\n");
        return EXIT_FAILURE;
    }

    printf("%.10g\n", perimeter);
    return EXIT_SUCCESS;
}