#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double sphere_volume(double radius);

double sphere_volume(double radius)
{
    return (4.0 / 3.0) * PI * radius * radius * radius;
}

int main(void)
{
    double radius = 0.0;
    double volume = 0.0;

    printf("Enter the radius of the sphere: ");

    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius)) {
        fprintf(stderr, "Error: radius is not a finite number.\n");
        return EXIT_FAILURE;
    }

    volume = sphere_volume(radius);

    if (!isfinite(volume)) {
        fprintf(stderr, "Error: volume computation overflowed.\n");
        return EXIT_FAILURE;
    }

    printf("The volume of the sphere with radius %.6f is %.6f\n", radius, volume);

    return EXIT_SUCCESS;
}