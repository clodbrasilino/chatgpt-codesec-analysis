#include <stdio.h>
#include <math.h>

static int sector_area(double radius, double angle_degrees, double *area)
{
    if (area == NULL || !isfinite(radius) || !isfinite(angle_degrees) ||
        radius < 0.0 || angle_degrees < 0.0 || angle_degrees > 360.0) {
        return 0;
    }

    const double pi = acos(-1.0);
    const double result = pi * radius * radius * angle_degrees / 360.0;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    double radius;
    double angle_degrees;
    double area;

    printf("Enter radius and angle in degrees: ");

    if (scanf("%lf %lf", &radius, &angle_degrees) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (!sector_area(radius, angle_degrees, &area)) {
        fprintf(stderr, "Radius and angle must be finite; radius must be nonnegative, and angle must be between 0 and 360 degrees.\n");
        return 1;
    }

    printf("Area of the sector: %.6f\n", area);
    return 0;
}