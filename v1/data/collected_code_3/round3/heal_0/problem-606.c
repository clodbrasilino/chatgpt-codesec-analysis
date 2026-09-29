#include <stdio.h>
#include <math.h>

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

int main() {
    double degrees;
    printf("Enter degrees: ");
    scanf("%lf", &degrees);
    printf("Radians: %lf\n", degreesToRadians(degrees));
    return 0;
}