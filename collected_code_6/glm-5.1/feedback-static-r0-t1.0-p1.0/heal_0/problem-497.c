#include <stdio.h>
#include <math.h>
#include <errno.h>

double cone_surface_area(double radius, double slant_height) {
    if (radius < 0.0 || slant_height < 0.0) {
        errno = EDOM;
        return NAN;
    }
    return M_PI * radius * (radius + slant_height);
}

int main(void) {
    double radius = 3.0;
    double slant_height = 5.0;
    
    errno = 0;
    double area = cone_surface_area(radius, slant_height);
    
    if (errno != 0 || isnan(area)) {
        return 1;
    }
    
    printf("%f\n", area);
    return 0;
}