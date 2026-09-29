#include <stdio.h>
#include <math.h>

double degrees_to_radians(double degrees)
{
    return degrees * (M_PI / 180.0);
}

int main(void)
{
    double degrees;
    double radians;

    printf("Enter degrees: ");

    if (scanf("%lf", &degrees) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    radians = degrees_to_radians(degrees);
    printf("Radians: %f\n", radians);

    return 0;
}