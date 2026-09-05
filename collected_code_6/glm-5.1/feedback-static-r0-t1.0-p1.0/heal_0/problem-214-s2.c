#include <stdio.h>
#include <math.h>

double radians_to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

int main(void) {
    double rad = 1.0471975512;
    double deg = radians_to_degrees(rad);
    printf("%f\n", deg);
    return 0;
}