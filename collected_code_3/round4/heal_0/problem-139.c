#include <stdio.h>

#define PI 3.14159

double findCircumference(double radius) {
    return 2 * PI * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);
    printf("Circumference of the circle is: %.2lf\n", findCircumference(radius));
    return 0;
}