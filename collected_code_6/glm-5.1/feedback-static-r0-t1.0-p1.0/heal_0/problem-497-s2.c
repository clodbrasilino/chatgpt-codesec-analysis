#include <stdio.h>
#include <math.h>

double calculate_cone_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    double slant_height = sqrt((radius * radius) + (height * height));
    return (M_PI * radius * radius) + (M_PI * radius * slant_height);
}

int main() {
    double radius = 3.0;
    double height = 4.0;
    double surface_area = calculate_cone_surface_area(radius, height);
    if (surface_area < 0.0) {
        return 1;
    }
    printf("Surface Area: %f\n", surface_area);
    return 0;
}