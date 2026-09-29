#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <float.h>

double calculate_arc_length(double radius, double angle_degrees) {
    if (radius < 0.0 || !isfinite(radius) || !isfinite(angle_degrees)) {
        errno = EDOM;
        return -1.0;
    }
    
    if (radius == 0.0 || angle_degrees == 0.0) {
        return 0.0;
    }
    
    double angle_radians = angle_degrees * (M_PI / 180.0);
    
    if (fabs(angle_radians) > DBL_MAX / radius) {
        errno = ERANGE;
        return -1.0;
    }
    
    return radius * angle_radians;
}

int main(void) {
    double radius = 5.0;
    double angle = 60.0;
    
    errno = 0;
    double arc_length = calculate_arc_length(radius, angle);
    
    if (arc_length < 0.0 && errno != 0) {
        perror("Error calculating arc length");
        return 1;
    }
    
    printf("Arc length: %f\n", arc_length);
    return 0;
}