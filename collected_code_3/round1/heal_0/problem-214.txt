#include <stdio.h>
#include <math.h>

double radiansToDegrees(double radians) {
    double degrees;
    degrees = radians * (180.0 / M_PI);
    return degrees;
}

int main() {
    double radians = 1.0;
    double degrees;

    degrees = radiansToDegrees(radians);
    printf("Degrees: %f\n", degrees);

    return 0;
}