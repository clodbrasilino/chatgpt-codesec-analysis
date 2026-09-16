#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11.785714285714285, got <no output>
  *  test case 0 failed: expected 3.5357142857142856, got <no output>
  */

double arc_length(double radius, double angle_degrees) {
    if (radius < 0) {
        fprintf(stderr, "Error: radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    if (angle_degrees < 0 || angle_degrees > 360) {
        fprintf(stderr, "Error: angle must be between 0 and 360 degrees\n");
        exit(EXIT_FAILURE);
    }
    
    double angle_radians = angle_degrees * M_PI / 180.0;
    return radius * angle_radians;
}

int main(void) {
    double radius;
    double angle;
    int result;

    printf("Enter radius: ");
    fflush(stdout);
    result = scanf("%lf", &radius);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for radius\n");
        return EXIT_FAILURE;
    }

    printf("Enter angle in degrees: ");
    fflush(stdout);
    result = scanf("%lf", &angle);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for angle\n");
        return EXIT_FAILURE;
    }

    double length = arc_length(radius, angle);
    printf("Arc length: %.6f\n", length);

    return EXIT_SUCCESS;
}