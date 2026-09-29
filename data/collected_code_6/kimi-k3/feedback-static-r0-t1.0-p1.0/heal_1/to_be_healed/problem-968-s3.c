#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'strerror' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

#define STEPS 100000
#define PI 3.14159265358979323846

typedef struct {
    double amplitude;
    double frequency;
    double phase;
    double offset;
} periodic_func_params;

static double periodic_function(double x, const periodic_func_params *params)
{
    if (params == NULL) {
        errno = EINVAL;
        return NAN;
    }
    return params->amplitude * sin(params->frequency * x + params->phase) + params->offset;
}

static int find_maximum(double start, double end, const periodic_func_params *params, 
                        double *max_value, double *max_x)
{
    double step;
    /* Possible weaknesses found:
     *  The scope of the variable 'x' can be reduced. [variableScope]
     */
    double x;
    /* Possible weaknesses found:
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    double current;
    int i;

    if (params == NULL || max_value == NULL || max_x == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (!isfinite(start) || !isfinite(end) || start >= end) {
        errno = ERANGE;
        return -1;
    }

    step = (end - start) / (double)STEPS;
    *max_value = -DBL_MAX;
    *max_x = start;

    for (i = 0; i <= STEPS; i++) {
        x = start + (double)i * step;
        current = periodic_function(x, params);
        
        if (isnan(current)) {
            errno = EDOM;
            return -1;
        }

        if (current > *max_value) {
            *max_value = current;
            *max_x = x;
        }
    }

    return 0;
}

int main(void)
{
    periodic_func_params params = {1.0, 2.0 * PI, 0.0, 0.0};
    double max_value;
    double max_x;
    double start = 0.0;
    double end = 2.0 * PI;
    int result;

    result = find_maximum(start, end, &params, &max_value, &max_x);

    if (result != 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strerror' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strerror'
         *  call to undeclared library function 'strerror' with type 'char *(int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Maximum value: %f\n", max_value);
    printf("At x = %f\n", max_x);

    return EXIT_SUCCESS;
}