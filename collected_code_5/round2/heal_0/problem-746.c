#include <stdio.h>
#define PI 3.14

double findSectorArea(double radius, double angle) {
    if (radius < 0 || angle < 0) {
        return -1;
    }
    
    double area = PI * radius * radius * (angle / 360);
    return area;
}

int main() {
    double radius, angle;
    
    printf("Enter radius: ");
    scanf("%lf", &radius);
    printf("Enter angle in degree: ");
    scanf("%lf", &angle);
    
    double area = findSectorArea(radius, angle);

    if (area < 0) {
        printf("Invalid input. Radius and angle must be positive.\n");
    } else {
        printf("Area of the sector: %0.2lf\n", area);
    }

    return 0;
}