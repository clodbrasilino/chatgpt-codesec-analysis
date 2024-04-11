#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double calculateSectorArea(double radius, double angle) {
    if (angle >= 360) {
        printf("Angle is not possible\n");
        return 0;
    }
    double sectorArea = PI * (radius * radius) * (angle / 360);
    return sectorArea;
}

int main() {
    double radius, angle;
    printf("Enter radius of the circle: ");
    scanf("%lf", &radius);
    printf("Enter angle of the sector: ");
    scanf("%lf", &angle);
    double area = calculateSectorArea(radius, angle);
    printf("Area of sector is: %.2lf\n", area);
    return 0;
}