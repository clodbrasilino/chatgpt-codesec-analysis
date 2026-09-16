#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>

#define PI 3.14159265358979323846

int calculate_arc_length(double radius, double angle_degrees, double *result)
{
    double angle_radians;

    if (result == NULL)
    {
        return -1;
    }

    if (radius < 0.0 || !isfinite(radius))
    {
        return -1;
    }

    if (!isfinite(angle_degrees))
    {
        return -1;
    }

    angle_radians = angle_degrees * PI / 180.0;

    if (fabs(angle_radians) > DBL_MAX / radius && radius > 0.0)
    {
        return -1;
    }

    *result = radius * angle_radians;

    if (!isfinite(*result))
    {
        return -1;
    }

    return 0;
}

int main(void)
{
    double radius;
    double angle;
    double arc_length;
    int status;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1)
    {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }

    printf("Enter angle in degrees: ");
    if (scanf("%lf", &angle) != 1)
    {
        fprintf(stderr, "Invalid input for angle\n");
        return 1;
    }

    status = calculate_arc_length(radius, angle, &arc_length);

    if (status != 0)
    {
        fprintf(stderr, "Error calculating arc length\n");
        return 1;
    }

    printf("Arc length: %f\n", arc_length);

    return 0;
}