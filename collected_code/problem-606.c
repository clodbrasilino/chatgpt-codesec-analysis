#include<stdio.h>

double degreesToRadians(double degrees) {
    double radians = degrees * (M_PI/180);
    return radians;
}

int main() {
    double degrees;
    printf("Enter degrees: ");
    scanf("%lf", &degrees);
    double radians = degreesToRadians(degrees);
    printf("Radians: %lf", radians);
    return 0;
}