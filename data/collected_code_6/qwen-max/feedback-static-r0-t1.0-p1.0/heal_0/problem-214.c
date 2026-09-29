#include <stdio.h>
#include <math.h>

double radian_to_degree(double radians) {
    return radians * (180.0 / M_PI);
}

int main() {
    double radians = 1.57;
    double degrees = radian_to_degree(radians);
    printf("%.2f radians is equal to %.2f degrees\n", radians, degrees);
    return 0;
}