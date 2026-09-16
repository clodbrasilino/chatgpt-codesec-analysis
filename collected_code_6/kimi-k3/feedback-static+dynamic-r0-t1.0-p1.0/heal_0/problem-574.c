#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>

#define PI 3.14159265358979323846

double cylinder_surface_area(double radius, double height)
{
    if (radius < 0.0 || height < 0.0)
    {
        errno = EDOM;
        return -1.0;
    }
    
    double lateral_area = 2.0 * PI * radius * height;
    double base_area = PI * radius * radius;
    double total_area = lateral_area + (2.0 * base_area);
    
    if (total_area > DBL_MAX)
    {
        errno = ERANGE;
        return -1.0;
    }
    
    return total_area;
}

int main(void)
{
    double radius = 0.0;
    double height = 0.0;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1)
    {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }
    
    printf("Enter height: ");
    if (scanf("%lf", &height) != 1)
    {
        fprintf(stderr, "Invalid input for height\n");
        return 1;
    }
    
    errno = 0;
    double surface_area = cylinder_surface_area(radius, height);
    
    if (errno == EDOM)
    {
        fprintf(stderr, "Radius and height must be non-negative\n");
        return 1;
    }
    else if (errno == ERANGE)
    {
        fprintf(stderr, "Result out of range\n");
        return 1;
    }
    
    printf("Surface area: %.6f\n", surface_area);
    
    return 0;
}