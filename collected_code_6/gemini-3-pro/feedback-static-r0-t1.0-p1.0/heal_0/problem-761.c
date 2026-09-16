#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

int calculate_arc_length(double radius, double angle_degrees, double *arc_length);

int calculate_arc_length(double radius, double angle_degrees, double *arc_length) {
    double angle_radians;

    if (radius < 0.0 || arc_length == NULL) {
        return -1;
    }

    angle_radians = angle_degrees * (PI / 180.0);
    *arc_length = radius * angle_radians;

    return 0;
}

int main(void) {
    double radius = 10.0;
    double angle_degrees = 90.0;
    double arc_length = 0.0;
    int status;

    status = calculate_arc_length(radius, angle_degrees, &arc_length);

    if (status != 0) {
        fprintf(stderr, "Invalid input parameters provided.\n");
        return EXIT_FAILURE;
    }

    printf("Radius: %.2f\n", radius);
    printf("Angle (degrees): %.2f\n", angle_degrees);
    printf("Arc Length: %.4f\n", arc_length);

    status = calculate_arc_length(-5.0, 45.0, &arc_length);

    if (status != 0) {
        printf("Error handling test passed for negative radius.\n");
    }

    return EXIT_SUCCESS;
}