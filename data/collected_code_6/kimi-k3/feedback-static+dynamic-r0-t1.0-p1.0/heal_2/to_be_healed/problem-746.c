#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6.285714285714286, got <no output>
  *  test case 1 failed: expected 31.82142857142857, got <no output>
  */

double sectorArea(double radius, double angleDegrees) {
    if (radius < 0.0 || angleDegrees < 0.0 || angleDegrees > 360.0) {
        return -1.0;
    }
    return (angleDegrees / 360.0) * M_PI * radius * radius;
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