#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793238

double cylinder_surface_area(double radius, double height) {
    return 2 * PI * radius * (radius + height);
}

int main() {
    double radius, height;

    printf("Enter radius of the cylinder: ");
    scanf("%lf", &radius);

    printf("Enter height of the cylinder: ");
    scanf("%lf", &height);

    printf("Surface area of the cylinder is: %.2lf\n", cylinder_surface_area(radius, height));

    return 0;
}