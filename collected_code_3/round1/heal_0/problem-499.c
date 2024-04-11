#include <stdio.h>

#define PI 3.14159

double findDiameter(double radius) {
    return 2 * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);
    printf("Diameter of the circle is: %.2lf\n", findDiameter(radius));
    return 0;
}