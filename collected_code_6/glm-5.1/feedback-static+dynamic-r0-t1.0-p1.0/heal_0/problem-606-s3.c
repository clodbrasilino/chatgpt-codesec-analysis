#include <stdio.h>
#include <math.h>

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

int main(int argc, char *argv[]) {
    double degrees = 180.0;
    double radians = degrees_to_radians(degrees);
    
    if (isfinite(radians)) {
        printf("%f\n", radians);
        return 0;
    } else {
        return 1;
    }
}