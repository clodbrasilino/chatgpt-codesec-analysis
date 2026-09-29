#include <stdio.h>
#include <math.h>

double cone_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    double slant_height = sqrt((radius * radius) + (height * height));
    return (M_PI * radius * (radius + slant_height));
}

int main(void) {
    double radius = 3.0;
    double height = 4.0;
    double area = cone_surface_area(radius, height);
    if (area < 0.0) {
        return 1;
    }
    printf("%f\n", area);
    return 0;
}