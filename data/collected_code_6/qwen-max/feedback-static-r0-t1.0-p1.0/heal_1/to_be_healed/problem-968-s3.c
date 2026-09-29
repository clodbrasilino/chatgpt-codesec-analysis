#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  *  include '<math.h>' or provide a declaration of 'sin'
  */

double periodic_function(double x) {
    /* Possible weaknesses found:
     *  include '<math.h>' or provide a declaration of 'cos'
     *  call to undeclared library function 'sin' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'cos'
     *  implicit declaration of function 'sin' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'sin'
     *  call to undeclared library function 'cos' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'cos' [-Wimplicit-function-declaration]
     */
    return 3 * sin(x) + 4 * cos(2 * x);
}

double find_maximum_periodic_value(double (*func)(double), double start, double end, double step) {
    /* Possible weaknesses found:
     *  'DBL_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'DBL_MAX'
     */
    double max_value = -DBL_MAX;
    for (double x = start; x <= end; x += step) {
        double value = func(x);
        if (value > max_value) {
            max_value = value;
        }
    }
    return max_value;
}

int main() {
    /* Possible weaknesses found:
     *  use of undeclared identifier 'M_PI'
     *  'M_PI' undeclared (first use in this function)
     */
    double max_val = find_maximum_periodic_value(periodic_function, 0.0, 2 * M_PI, 0.01);
    printf("Maximum value: %f\n", max_val);
    return 0;
}