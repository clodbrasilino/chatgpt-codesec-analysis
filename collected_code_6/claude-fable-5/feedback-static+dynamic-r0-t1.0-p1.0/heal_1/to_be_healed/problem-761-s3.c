#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3.5357142857142856, got 7.0685834884643555
  *  test case 1 failed: expected 11.785714285714285, got 23.561944961547852
  */

double arc_length(double radius, double angle_degrees)
{
    return (PI / 180.0) * angle_degrees * radius;
}

int main(void)
{
    double radius;
    double angle;
    double result;

    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the angle in degrees: ");
    if (scanf("%lf", &angle) != 1) {
        fprintf(stderr, "Error: invalid input for angle.\n");
        return EXIT_FAILURE;
    }

    if (angle < 0.0 || angle > 360.0) {
        fprintf(stderr, "Error: angle must be between 0 and 360 degrees.\n");
        return EXIT_FAILURE;
    }

    result = arc_length(radius, angle);

    if (isnan(result) || isinf(result)) {
        fprintf(stderr, "Error: calculation resulted in an invalid value.\n");
        return EXIT_FAILURE;
    }

    printf("Arc length: %.6f\n", result);

    return EXIT_SUCCESS;
}