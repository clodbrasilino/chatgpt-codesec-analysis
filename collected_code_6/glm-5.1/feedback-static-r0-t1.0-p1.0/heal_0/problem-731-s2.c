#include <stdio.h>
#include <math.h>

double cone_lateral_surface_area(double radius, double slant_height) {
    if (radius < 0.0 || slant_height < 0.0) {
        return -1.0;
    }
    return M_PI * radius * slant_height;
}

int main(void) {
    double radius = 5.0;
    double slant_height = 10.0;
    double area = cone_lateral_surface_area(radius, slant_height);
    
    if (area < 0.0) {
        return 1;
    }
    
    printf("%f\n", area);
    return 0;
}