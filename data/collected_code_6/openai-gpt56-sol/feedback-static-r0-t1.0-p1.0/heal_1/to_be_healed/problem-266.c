#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int cube_lateral_surface_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side < 0.0 ||
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'DBL_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'DBL_MAX'
         */
        side > sqrt(DBL_MAX / 4.0)) {
        return 0;
    }

    *area = 4.0 * side * side;
    return isfinite(*area);
}

int main(void)
{
    double side;
    double area;

    if (printf("Enter the side length of the cube: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!cube_lateral_surface_area(side, &area)) {
        fprintf(stderr, "The side length must be finite, nonnegative, and within range.\n");
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}