#include <stdio.h>
#include <math.h>

void polar_to_rectangular(double radius, double angle_degrees, double *x, double *y)
{
    double angle_radians;
    
    if (x == NULL || y == NULL)
    {
        return;
    }
    
    angle_radians = angle_degrees * M_PI / 180.0;
    *x = radius * cos(angle_radians);
    *y = radius * sin(angle_radians);
}

int main(void)
{
    double radius = 5.0;
    double angle = 45.0;
    double x = 0.0;
    double y = 0.0;
    
    polar_to_rectangular(radius, angle, &x, &y);
    
    printf("Polar: (r=%.2f, θ=%.2f°)\n", radius, angle);
    printf("Rectangular: (x=%.2f, y=%.2f)\n", x, y);
    
    return 0;
}