#include <stdio.h>
#include <math.h>

double radians_to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

int main() {
    double rad = 1.0;
    double deg = radians_to_degrees(rad);
    printf("%f radians is equal to %f degrees.\n", rad, deg);
    return 0;
}