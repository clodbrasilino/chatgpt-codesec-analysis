#include <stdio.h>

#define PI 3.14159

double calculateCircumference(double radius) {
    return 2 * PI * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);
    double circumference = calculateCircumference(radius);
    printf("The circumference of the circle is: %.2lf\n", circumference);
    return 0;
}