#include <stdio.h>
#include <math.h>

double cylinder_surface_area(double radius) {
    return M_PI * radius * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the cylinder: ");
    scanf("%lf", &radius);
    double area = cylinder_surface_area(radius);
    printf("The top or bottom surface area of the cylinder is: %.2lf\n", area);
    return 0;
}