#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double radians_to_degrees(double radians);

double radians_to_degrees(double radians)
{
    return radians * (180.0 / M_PI);
}

int main(void)
{
    double radians = 0.0;
    double degrees = 0.0;

    printf("Enter angle in radians: ");
    if (scanf("%lf", &radians) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    degrees = radians_to_degrees(radians);

    if (printf("%f radians = %f degrees\n", radians, degrees) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}