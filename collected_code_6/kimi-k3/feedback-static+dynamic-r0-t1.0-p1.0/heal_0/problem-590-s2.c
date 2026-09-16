#include <stdio.h>
#include <math.h>

void polar_to_rectangular(double radius, double angle_degrees, double *x, double *y) {
    if (x == NULL || y == NULL) {
        return;
    }
    
    if (radius < 0.0) {
        *x = 0.0;
        *y = 0.0;
        return;
    }
    
    double angle_radians = angle_degrees * M_PI / 180.0;
    *x = radius * cos(angle_radians);
    *y = radius * sin(angle_radians);
}

int main(void) {
    double radius, angle, x, y;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }
    
    printf("Enter angle in degrees: ");
    if (scanf("%lf", &angle) != 1) {
        fprintf(stderr, "Invalid input for angle\n");
        return 1;
    }
    
    polar_to_rectangular(radius, angle, &x, &y);
    
    printf("Rectangular coordinates: (%.2f, %.2f)\n", x, y);
    
    return 0;
}