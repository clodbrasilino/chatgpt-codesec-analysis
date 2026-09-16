#include <stdio.h>
#include <math.h>

double lateral_surface_area_cone(double radius, double slant_height) {
    if (radius < 0.0 || slant_height < 0.0) {
        return -1.0;
    }
    return M_PI * radius * slant_height;
}

int main(void) {
    double r = 3.0;
    double l = 5.0;
    double area = lateral_surface_area_cone(r, l);

    if (area < 0.0) {
        return 1;
    }

    printf("%f\n", area);
    return 0;
}