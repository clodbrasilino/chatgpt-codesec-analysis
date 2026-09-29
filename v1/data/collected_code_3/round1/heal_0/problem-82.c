#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793238

double sphere_volume(double radius) {
    return (4.0/3.0) * PI * pow(radius, 3);
}

int main() {
    double radius;

    printf("Enter the radius of the sphere: ");
    scanf("%lf", &radius);

    printf("Volume of the sphere is: %.2lf\n", sphere_volume(radius));

    return 0;
}