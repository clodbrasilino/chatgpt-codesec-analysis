#include <stdio.h>
#include <math.h>

double lateral_surface_area_cone(double radius, double height) {
    double slant_height = sqrt(radius * radius + height * height);
    return M_PI * radius * slant_height;
}

int main() {
    double radius = 3.0;
    double height = 4.0;
    double area = lateral_surface_area_cone(radius, height);
    printf("The lateral surface area of the cone is: %f\n", area);
    return 0;
}