#include <stdio.h>
#include <math.h>

double findLateralSurfaceArea(double radius, double height) {
    return 2 * M_PI * radius * height;
}

int main() {
    double radius, height;
    printf("Enter radius of the cylinder: ");
    scanf("%lf", &radius);
    printf("Enter height of the cylinder: ");
    scanf("%lf", &height);
    printf("Lateral Surface Area of the cylinder is: %.2lf", findLateralSurfaceArea(radius, height));
    return 0;
}