#include <stdio.h>
#include <math.h>

double radiansToDegrees(double radians) {
    double degrees;
    degrees = radians * (180.0 / M_PI);
    return degrees;
}

int main() {
    double radians;
    printf("Enter radians: ");
    scanf("%lf", &radians);
    printf("Degrees: %lf\n", radiansToDegrees(radians));
    return 0;
}