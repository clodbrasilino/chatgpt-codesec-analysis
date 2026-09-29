#include <stdio.h>
#include <math.h>
#include <errno.h>

double cylinder_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        errno = EDOM;
        return NAN;
    }
    return 2.0 * M_PI * radius * (radius + height);
}

int main(void) {
    double radius = 3.0;
    double height = 5.0;
    
    errno = 0;
    double area = cylinder_surface_area(radius, height);
    
    if (errno == EDOM) {
        return 1;
    }
    
    printf("%f\n", area);
    return 0;
}