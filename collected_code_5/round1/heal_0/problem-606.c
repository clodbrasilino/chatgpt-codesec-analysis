#include <stdio.h>
#include <math.h>

double degreesToRadians(double degrees) {
    double radians = degrees * ( M_PI / 180.0 );
    return radians;
}

int main() {
    double degrees;
    printf("Enter degrees: ");
    if(scanf("%lf", &degrees) != 1) {
        printf("Invalid input. Please enter a number.\n");
        return 1;
    }
    double result = degreesToRadians(degrees);

    printf("Degrees in radians: %f\n", result);

    return 0;
}