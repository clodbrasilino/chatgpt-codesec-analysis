#include <stdio.h>
#include <math.h>

double lateral_surface_area(double radius, double height) {
    return M_PI * radius * sqrt((radius * radius) + (height * height));
}

int main() {
    double radius, height;
    printf("Enter radius of the cone: ");
    scanf("%lf", &radius);
    printf("Enter height of the cone: ");
    scanf("%lf", &height);
    printf("Lateral Surface Area of the cone is: %.2lf", lateral_surface_area(radius, height));
    return 0;
}