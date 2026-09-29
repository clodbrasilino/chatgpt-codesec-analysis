#include <stdio.h>

#define PI 3.14159265358979323846

double calculateCylinderPerimeter(double radius, double height);

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double perimeter = 0.0;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        return 1;
    }

    if (radius < 0.0 || height < 0.0) {
        return 1;
    }

    perimeter = calculateCylinderPerimeter(radius, height);

    printf("%.2f\n", perimeter);

    return 0;
}

double calculateCylinderPerimeter(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return (4.0 * radius) + (2.0 * height);
}