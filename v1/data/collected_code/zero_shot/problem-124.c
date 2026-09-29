#include <stdio.h>
#include <math.h>

double getAngle(double real, double imag) {
    return atan2(imag, real) * (180.0 / M_PI);
}

int main() {
    double real, imag;
    printf("Enter the real part of the complex number: ");
    scanf("%lf", &real);
    printf("Enter the imaginary part of the complex number: ");
    scanf("%lf", &imag);
    printf("The angle of the complex number is: %.2lf\n", getAngle(real, imag));
    return 0;
}