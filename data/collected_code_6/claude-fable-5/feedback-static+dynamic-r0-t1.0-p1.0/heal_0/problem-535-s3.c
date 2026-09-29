#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define PI 3.14159265358979323846

double cylinder_end_area(double radius);

double cylinder_end_area(double radius)
{
    return PI * radius * radius;
}

int main(void)
{
    double radius = 0.0;
    double area = 0.0;
    int result = 0;

    printf("Enter the radius of the cylinder: ");
    result = scanf("%lf", &radius);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (radius > sqrt(DBL_MAX / PI)) {
        fprintf(stderr, "Error: radius too large, result would overflow.\n");
        return EXIT_FAILURE;
    }

    area = cylinder_end_area(radius);
    printf("The surface area of the cylinder's end is: %f\n", area);

    return EXIT_SUCCESS;
}