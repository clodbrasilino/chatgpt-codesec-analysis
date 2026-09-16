#include <stdio.h>
#include <math.h>

double find_sector_area(double radius, double angle) {
    if (radius < 0 || angle < 0 || angle > 360) {
        return -1;
    }
    return (M_PI * radius * radius * (angle / 360.0));
}

int main() {
    double radius = 5.0;
    double angle = 90.0;
    double area = find_sector_area(radius, angle);
    if (area >= 0) {
        printf("Area of the sector: %f\n", area);
    } else {
        printf("Invalid input for radius or angle.\n");
    }
    return 0;
}