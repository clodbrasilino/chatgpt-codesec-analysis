#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double calculateSectorArea(double radius, double angle) {
    if (angle >= 360) {
        printf("Angle cannot be 360 degrees or more. Please enter a valid angle.\n");
        return -1;
    }
    double sectorArea = (PI * radius * radius * angle) / 360;
    return sectorArea;
}

int main() {
    double radius, angle;
    printf("Enter radius of the circle: ");
    scanf("%lf", &radius);
    printf("Enter angle of the sector: ");
    scanf("%lf", &angle);
    double area = calculateSectorArea(radius, angle);
    if (area != -1) {
        printf("Area of the sector is: %.2lf\n", area);
    }
    return 0;
}