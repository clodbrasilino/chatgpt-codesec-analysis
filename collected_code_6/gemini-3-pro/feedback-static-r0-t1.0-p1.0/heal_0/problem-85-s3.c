#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculateSphereSurfaceArea(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 4.0 * M_PI * radius * radius;
}

int main(void) {
    double radius;
    double area;

    printf("Enter the radius of the sphere: ");
    if (scanf("%lf", &radius) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    area = calculateSphereSurfaceArea(radius);

    if (area < 0.0) {
        printf("Radius cannot be negative.\n");
        return 1;
    }

    printf("Surface area of the sphere: %.2f\n", area);

    return 0;
}