#include <stdio.h>
#include <math.h>

double surfaceArea(double radius) {
    return M_PI * radius * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the cylinder: ");
    scanf("%lf", &radius);
    double area = surfaceArea(radius);
    printf("The surface area of the top or bottom of the cylinder is: %.2lf\n", area);
    return 0;
}