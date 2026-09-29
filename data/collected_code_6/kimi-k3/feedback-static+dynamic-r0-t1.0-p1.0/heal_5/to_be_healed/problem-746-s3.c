#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6.285714285714286, got 6.2831854820251465
  *  test case 1 failed: expected 31.82142857142857, got 31.808626174926758
  */

double find_sector_area(double radius, double angle_degrees) {
    if (radius < 0.0 || angle_degrees < 0.0) {
        return -1.0;
    }
    return (angle_degrees / 360.0) * M_PI * radius * radius;
}

int main(void) {
    double radius, angle, area;
    
    if (scanf("%lf %lf", &radius, &angle) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    area = find_sector_area(radius, angle);
    
    if (area < 0.0) {
        fprintf(stderr, "Invalid input: radius and angle must be non-negative\n");
        return 1;
    }
    
    printf("%.15f\n", area);
    
    return 0;
}