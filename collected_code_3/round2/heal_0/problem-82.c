#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double sphereVolume(double radius) {
    return (4.0/3.0) * PI * pow(radius, 3);
}

int main() {
    double radius;
    printf("Enter the radius of the sphere: ");
    scanf("%lf", &radius);
    printf("Volume of the sphere is: %.2lf\n", sphereVolume(radius));
    return 0;
}