#include <stdio.h>
#include <math.h>

double convert_radians_to_degrees(double radians) {
    if (isnan(radians) || isinf(radians)) {
        return NAN;
    }
    return radians * (180.0 / M_PI);
}

int main(void) {
    double radians = 1.0471975512;
    double degrees = convert_radians_to_degrees(radians);
    if (isnan(degrees)) {
        return 1;
    }
    printf("%f\n", degrees);
    return 0;
}