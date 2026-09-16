#include <stdio.h>

#define PI 3.14159265358979323846

double radians_to_degrees(double radians) {
    return radians * (180.0 / PI);
}

int main(void) {
    double radians = 1.0;
    double degrees = radians_to_degrees(radians);
    
    printf("%f radians is equal to %f degrees.\n", radians, degrees);
    
    return 0;
}