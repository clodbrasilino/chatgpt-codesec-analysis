#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

double find_minimum(double (*func)(double), double period, double start, double tolerance) {
    if (func == NULL || period <= 0.0 || tolerance <= 0.0 || !isfinite(period) || !isfinite(start) || !isfinite(tolerance)) {
        return NAN;
    }

    double a = start;
    double b = start + period;
    double gr = (sqrt(5.0) - 1.0) / 2.0;
    
    double c = b - gr * (b - a);
    double d = a + gr * (b - a);
    
    double fc = func(c);
    double fd = func(d);
    
    if (!isfinite(fc) || !isfinite(fd)) {
        return NAN;
    }
    
    while (fabs(b - a) > tolerance) {
        if (fc < fd) {
            b = d;
            d = c;
            fd = fc;
            c = b - gr * (b - a);
            fc = func(c);
        } else {
            a = c;
            c = d;
            fc = fd;
            d = a + gr * (b - a);
            fd = func(d);
        }
        
        if (!isfinite(fc) || !isfinite(fd)) {
            return NAN;
        }
    }
    
    return func((a + b) / 2.0);
}

double periodic_function(double x) {
    return sin(x) + cos(2.0 * x);
}

int main(void) {
    double period = 2.0 * M_PI;
    double start = 0.0;
    double tolerance = 1e-10;
    
    double min_value = find_minimum(periodic_function, period, start, tolerance);
    
    if (isnan(min_value)) {
        fprintf(stderr, "Error: Failed to find minimum\n");
        return EXIT_FAILURE;
    }
    
    printf("Minimum value: %.10f\n", min_value);
    
    return EXIT_SUCCESS;
}