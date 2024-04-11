#include <stdio.h>
#include <math.h>

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

int main() {
    double degrees = 45.0;
    double radians = degreesToRadians(degrees);
    printf("Degrees: %.2f, Radians: %.2f\n", degrees, radians);
    return 0;
}