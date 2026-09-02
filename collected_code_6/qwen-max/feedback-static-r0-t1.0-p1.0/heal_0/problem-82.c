#include <stdio.h>
#include <math.h>

double sphere_volume(double radius) {
    return (4.0/3.0) * M_PI * pow(radius, 3);
}

int main() {
    double r = 5.0;
    printf("Volume of the sphere: %f\n", sphere_volume(r));
    return 0;
}