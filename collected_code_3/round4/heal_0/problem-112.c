#include <stdio.h>
#define PI 3.14159

double findPerimeter(double radius, double height) {
    return 2 * PI * (radius + height);
}

int main() {
    double radius, height;

    printf("Enter radius of the cylinder: ");
    scanf("%lf", &radius);

    printf("Enter height of the cylinder: ");
    scanf("%lf", &height);

    printf("Perimeter of the cylinder is: %.2lf\n", findPerimeter(radius, height));

    return 0;
}