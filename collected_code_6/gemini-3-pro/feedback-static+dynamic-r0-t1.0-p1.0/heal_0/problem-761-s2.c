#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_arc_length(double radius, double angle_degrees);

double calculate_arc_length(double radius, double angle_degrees) {
    if (radius < 0.0) {
        return -1.0;
    }
    
    double angle_radians = angle_degrees * (M_PI / 180.0);
    return radius * angle_radians;
}

int main(void) {
    double radius = 10.0;
    double angle_degrees = 45.0;
    
    double arc_length = calculate_arc_length(radius, angle_degrees);

    if (arc_length < 0.0) {
        fprintf(stderr, "Error: Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Arc Length: %.6f\n", arc_length);

    return EXIT_SUCCESS;
}