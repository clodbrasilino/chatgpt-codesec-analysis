#include <stdio.h>
#include <math.h>

double radians_to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

int main() {
    double radians = 1.57079632679;
    double degrees = radians_to_degrees(radians);
    printf("%.2f radians is %.2f degrees\n", radians, degrees);
    return 0;
}