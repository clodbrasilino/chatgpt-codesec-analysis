#include <stdio.h>
#include <math.h>

double calculate_sphere_surface_area(double radius) {
    if (radius < 0.0) {
        return NAN;
    }
    return 4.0 * M_PI * radius * radius;
}

int main(void) {
    double radius = 5.0;
    double surface_area = calculate_sphere_surface_area(radius);
    
    if (isnan(surface_area)) {
        fprintf(stderr, "Invalid radius value\n");
        return 1;
    }
    
    printf("%f\n", surface_area);
    return 0;
}