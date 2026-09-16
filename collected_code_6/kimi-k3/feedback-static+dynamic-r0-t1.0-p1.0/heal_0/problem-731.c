#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>

double calculate_lateral_surface_area(double radius, double slant_height);

int main(void) {
    double radius, slant_height, result;
    
    if (scanf("%lf %lf", &radius, &slant_height) != 2) {
        return 1;
    }
    
    if (radius < 0.0 || slant_height < 0.0) {
        return 1;
    }
    
    errno = 0;
    result = calculate_lateral_surface_area(radius, slant_height);
    
    if (errno != 0) {
        return 1;
    }
    
    printf("%.6f\n", result);
    
    return 0;
}

double calculate_lateral_surface_area(double radius, double slant_height) {
    double result;
    
    if (radius > DBL_MAX / (M_PI * slant_height)) {
        errno = ERANGE;
        return -1.0;
    }
    
    result = M_PI * radius * slant_height;
    
    return result;
}