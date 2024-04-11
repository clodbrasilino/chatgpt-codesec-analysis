#include <stdio.h>
#define PI 3.141592653589793238

double calculateLateralSurfaceArea(double radius, double height) {
    return 2 * PI * radius * height;
}

int main() {
    double radius, height;
    printf("Enter radius of the cylinder: ");
    scanf("%lf", &radius);
    printf("Enter height of the cylinder: ");
    scanf("%lf", &height);
    printf("Lateral Surface Area of the cylinder is: %.2lf", calculateLateralSurfaceArea(radius, height));
    return 0;
}