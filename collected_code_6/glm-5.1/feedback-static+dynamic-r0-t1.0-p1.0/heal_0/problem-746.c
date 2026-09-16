#include <stdio.h>
#include <math.h>

double area_of_sector(double radius, double angle_degrees) {
    if (radius < 0.0) {
        return -1.0;
    }
    if (angle_degrees < 0.0) {
        return -1.0;
    }
    if (angle_degrees > 360.0) {
        return -1.0;
    }
    double angle_radians = angle_degrees * M_PI / 180.0;
    double area = 0.5 * radius * radius * angle_radians;
    return area;
}

int main() {
    double radius = 5.0;
    double angle = 60.0;
    double area = area_of_sector(radius, angle);
    if (area < 0.0) {
        return 1;
    }
    printf("%f\n", area);
    return 0;
}