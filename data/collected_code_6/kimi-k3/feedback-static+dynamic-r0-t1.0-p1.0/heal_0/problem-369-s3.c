#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>

double calculate_lateral_surface_area(double length, double width, double height) {
    if (length < 0 || width < 0 || height < 0) {
        errno = EDOM;
        return -1.0;
    }
    if (length > DBL_MAX / 2.0 || width > DBL_MAX / 2.0 || height > DBL_MAX / 2.0) {
        errno = ERANGE;
        return -1.0;
    }
    return 2.0 * height * (length + width);
}

int main(void) {
    double length = 0.0;
    double width = 0.0;
    double height = 0.0;
    double result = 0.0;
    
    printf("Enter length, width, and height: ");
    
    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fprintf(stderr, "Error: Invalid input format\n");
        return 1;
    }
    
    if (length < 0 || width < 0 || height < 0) {
        fprintf(stderr, "Error: Dimensions must be non-negative\n");
        return 1;
    }
    
    result = calculate_lateral_surface_area(length, width, height);
    
    if (result < 0.0) {
        fprintf(stderr, "Error: Calculation failed (errno: %d)\n", errno);
        return 1;
    }
    
    printf("Lateral Surface Area: %.2f\n", result);
    
    return 0;
}