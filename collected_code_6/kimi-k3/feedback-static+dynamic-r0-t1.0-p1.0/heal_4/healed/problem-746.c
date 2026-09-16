#include <stdio.h>
#include <math.h>

double sectorArea(double radius, double angleDegrees) {
    if (radius < 0.0 || angleDegrees < 0.0 || angleDegrees > 360.0) {
        return -1.0;
    }
    return (angleDegrees / 360.0) * 3.14159265358979323846 * radius * radius;
}

int main(void) {
    double radius, angle, result;
    
    if (scanf("%lf %lf", &radius, &angle) != 2) {
        return 1;
    }
    
    result = sectorArea(radius, angle);
    
    if (result < 0.0) {
        return 1;
    }
    
    printf("%.15f\n", result);
    
    return 0;
}