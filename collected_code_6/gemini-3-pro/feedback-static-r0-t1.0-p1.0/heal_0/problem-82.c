#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculateSphereVolume(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return (4.0 / 3.0) * M_PI * pow(radius, 3.0);
}

int main(void) {
    double radius = 5.0;
    double volume;

    volume = calculateSphereVolume(radius);

    if (volume >= 0.0) {
        printf("Volume of sphere with radius %.2f is %.2f\n", radius, volume);
    } else {
        printf("Error: Radius cannot be negative.\n");
    }

    return 0;
}