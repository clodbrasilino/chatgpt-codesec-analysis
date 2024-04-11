#include <stdio.h>
#include <math.h>

double sphereVolume(double radius) {
    return (4.0/3.0) * M_PI * pow(radius, 3);
}

int main() {
    double radius;
    printf("Enter the radius of the sphere: ");
    scanf("%lf", &radius);
    printf("Volume of the sphere is: %.2lf\n", sphereVolume(radius));
    return 0;
}