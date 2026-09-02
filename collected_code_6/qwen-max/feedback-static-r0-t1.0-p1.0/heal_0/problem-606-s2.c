#include <stdio.h>
#include <math.h>

double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

int main() {
    double degrees = 180.0;
    double radians = degrees_to_radians(degrees);
    printf("%f degrees is %f radians\n", degrees, radians);
    return 0;
}