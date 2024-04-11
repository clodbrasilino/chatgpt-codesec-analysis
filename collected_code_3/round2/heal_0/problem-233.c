#include <stdio.h>
#define PI 3.141592653589793238

double lateral_surface_area(double radius, double height) {
    return 2 * PI * radius * height;
}

int main() {
    double radius, height;
    printf("Enter radius of the cylinder: ");
    scanf("%lf", &radius);
    printf("Enter height of the cylinder: ");
    scanf("%lf", &height);
    printf("Lateral Surface Area of Cylinder = %.2lf", lateral_surface_area(radius, height));
    return 0;
}