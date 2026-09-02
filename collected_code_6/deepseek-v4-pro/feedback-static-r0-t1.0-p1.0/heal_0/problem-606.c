#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

int main(void) {
    double degrees;
    
    printf("Enter angle in degrees: ");
    if (scanf("%lf", &degrees) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    double radians = degrees_to_radians(degrees);
    printf("%.2f degrees = %.6f radians\n", degrees, radians);
    
    return 0;
}