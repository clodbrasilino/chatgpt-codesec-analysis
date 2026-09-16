#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double cylinder_surface_area(double radius, int surface_type) {
    if (radius < 0.0) {
        fprintf(stderr, "Error: Radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    
    if (surface_type != 0 && surface_type != 1) {
        fprintf(stderr, "Error: surface_type must be 0 (top) or 1 (bottom)\n");
        exit(EXIT_FAILURE);
    }
    
    return PI * radius * radius;
}

int main(void) {
    double radius = 5.0;
    int surface_type = 0;
    
    double area = cylinder_surface_area(radius, surface_type);
    printf("The %s surface area of the cylinder is: %.2f\n", 
           surface_type == 0 ? "top" : "bottom", area);
    
    return 0;
}