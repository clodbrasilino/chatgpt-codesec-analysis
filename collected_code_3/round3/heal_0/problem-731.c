#include <stdio.h>
#include <math.h>

double cone_lateral_surface_area(double radius, double height) {
    return M_PI * radius * sqrt(radius * radius + height * height);
}

int main() {
    double radius, height;
    printf("Enter radius of the cone: ");
    scanf("%lf", &radius);
    printf("Enter height of the cone: ");
    scanf("%lf", &height);
    printf("Lateral Surface Area of the Cone = %.2lf", cone_lateral_surface_area(radius, height));
    return 0;
}