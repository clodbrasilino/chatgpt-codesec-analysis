#include <stdio.h>
#include <math.h>

double calculate_arc_length(double radius, double angle_in_degrees) {
    double angle_in_radians = (M_PI / 180.0) * angle_in_degrees;
    return radius * angle_in_radians;
}

int main() {
    double radius = 5.0;
    double angle = 60.0; // degrees
    double arc_length = calculate_arc_length(radius, angle);
    printf("The arc length is: %f\n", arc_length);
    return 0;
}