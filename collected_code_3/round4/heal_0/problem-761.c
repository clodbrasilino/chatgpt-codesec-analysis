#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double calculateArcLength(double radius, double angle) {
    double arcLength = 2 * PI * radius * (angle / 360.0);
    return arcLength;
}

int main() {
    double radius, angle;
    printf("Enter radius of the circle: ");
    scanf("%lf", &radius);
    printf("Enter angle in degrees: ");
    scanf("%lf", &angle);
    double arcLength = calculateArcLength(radius, angle);
    printf("Arc length is: %.2lf\n", arcLength);
    return 0;
}