#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
 /* Possible weaknesses found:
  *  test case 1 failed: expected 566.3586699569488, got 471.2388916015625
  *  test case 0 failed: expected 204.20352248333654, got 188.49555969238281
  *  test case 2 failed: expected 1521.8090132193388, got 1014.7344360351562
  */

double lateral_surface_area(double radius, double slant_height) {
    return PI * radius * slant_height;
}

int main(void) {
    double radius, slant_height, area;
    double diameter, height;

    if (scanf("%lf %lf", &diameter, &height) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (diameter <= 0 || height <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    radius = diameter / 2.0;
    slant_height = sqrt(radius * radius + height * height);
    area = lateral_surface_area(radius, slant_height);
    printf("%.13f\n", area);

    return 0;
}