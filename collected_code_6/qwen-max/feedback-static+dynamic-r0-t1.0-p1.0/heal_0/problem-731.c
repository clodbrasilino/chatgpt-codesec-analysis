#include <stdio.h>
#include <math.h>

double lateral_surface_area_cone(double radius, double height) {
    return M_PI * radius * sqrt(pow(radius, 2) + pow(height, 2));
}

int main() {
    double radius = 5.0;
    double height = 10.0;
    double area = lateral_surface_area_cone(radius, height);
    printf("The lateral surface area of the cone is: %.2f\n", area);
    return 0;
}