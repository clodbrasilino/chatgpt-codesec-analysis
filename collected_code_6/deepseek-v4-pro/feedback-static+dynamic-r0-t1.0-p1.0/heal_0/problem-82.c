#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double sphere_volume(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return (4.0 / 3.0) * M_PI * pow(radius, 3.0);
}

int main(void) {
    double radius;
    double volume;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    volume = sphere_volume(radius);
    if (volume < 0.0) {
        fprintf(stderr, "Radius must be non-negative\n");
        return 1;
    }

    printf("Volume: %.6f\n", volume);
    return 0;
}