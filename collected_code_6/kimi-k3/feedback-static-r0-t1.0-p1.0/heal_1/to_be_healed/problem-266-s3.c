#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

double lateral_surface_area_cube(double side)
{
    if (side < 0.0 || !isfinite(side)) {
        errno = EDOM;
        return -1.0;
    }
    
    /* Possible weaknesses found:
     *  use of undeclared identifier 'DBL_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'DBL_MAX' undeclared (first use in this function)
     */
    if (side > 0.0 && side > sqrt(DBL_MAX / 4.0)) {
        errno = ERANGE;
        return -1.0;
    }
    
    return 4.0 * side * side;
}

int main(void)
{
    char buffer[128];
    char *endptr;
    double side;
    double result;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    side = strtod(buffer, &endptr);
    
    if (errno != 0 || endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = lateral_surface_area_cube(side);
    
    if (errno != 0 || result < 0.0) {
        fprintf(stderr, "Error calculating lateral surface area\n");
        return EXIT_FAILURE;
    }
    
    printf("%.6f\n", result);
    
    return EXIT_SUCCESS;
}