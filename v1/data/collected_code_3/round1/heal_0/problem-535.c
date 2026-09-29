#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double calculateSurfaceArea(double radius) {
    return PI * pow(radius, 2);
}

int main() {
    double radius;
    printf("Enter the radius of the cylinder: ");
    scanf("%lf", &radius);
    double surfaceArea = calculateSurfaceArea(radius);
    printf("The surface area of the top or bottom of the cylinder is: %.2lf\n", surfaceArea);
    return 0;
}