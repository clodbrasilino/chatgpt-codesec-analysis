#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double calculate_sphere_surface_area(double radius)
{
    if (radius < 0.0) {
        errno = EDOM;
        return -1.0;
    }
    
    if (radius > sqrt(DBL_MAX / (4.0 * PI))) {
        errno = ERANGE;
        return -1.0;
    }
    
    return 4.0 * PI * radius * radius;
}

int main(void)
{
    double radius;
    double surface_area;
    
    printf("Enter the radius of the sphere: ");
    
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    surface_area = calculate_sphere_surface_area(radius);
    
    if (errno != 0) {
        fprintf(stderr, "Error: Invalid radius value\n");
        return EXIT_FAILURE;
    }
    
    printf("Surface area of the sphere: %.6f\n", surface_area);
    
    return EXIT_SUCCESS;
}