#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double sphereSurfaceArea(double radius) {
    return 4 * PI * pow(radius, 2);
}

int main() {
    double radius;

    printf("Enter the radius of the sphere: ");
    scanf("%lf", &radius);

    printf("Surface area of the sphere is: %.2lf\n", sphereSurfaceArea(radius));

    return 0;
}