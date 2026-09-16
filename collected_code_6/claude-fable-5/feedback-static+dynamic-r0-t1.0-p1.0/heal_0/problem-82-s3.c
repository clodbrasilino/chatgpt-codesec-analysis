#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sphere_volume(double radius)
{
    return (4.0 / 3.0) * M_PI * radius * radius * radius;
}

int main(void)
{
    double radius;
    double volume;

    printf("Enter the radius of the sphere: ");

    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    volume = sphere_volume(radius);

    printf("The volume of the sphere is: %f\n", volume);

    return EXIT_SUCCESS;
}