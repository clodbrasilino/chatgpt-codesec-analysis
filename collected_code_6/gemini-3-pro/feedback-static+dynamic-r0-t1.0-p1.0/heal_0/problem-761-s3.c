#include <stdio.h>
#include <stdlib.h>

int calculate_arc_length(double radius, double angle_radians, double *result) {
    if (result == NULL) {
        return -1;
    }
    if (radius < 0.0) {
        return -1;
    }
    
    *result = radius * angle_radians;
    
    return 0;
}

int main(void) {
    double radius = 10.5;
    double pi = 3.14159265358979323846;
    double angle_radians = pi / 3.0; 
    double arc_length = 0.0;
    int status = 0;

    status = calculate_arc_length(radius, angle_radians, &arc_length);

    if (status == 0) {
        printf("Arc length: %.4f\n", arc_length);
    } else {
        fprintf(stderr, "Error: Invalid input parameters.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}