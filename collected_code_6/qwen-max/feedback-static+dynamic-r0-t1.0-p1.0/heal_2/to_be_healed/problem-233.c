#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 314.15000000000003, got <no output>
  *  test case 2 failed: expected 251.32000000000002, got <no output>
  *  test case 1 failed: expected 125.66000000000001, got <no output>
  */

double lateral_surface_area_cylinder(double radius, double height) {
    return 2 * M_PI * radius * height;
}

int main() {
    double radius = 5.0;
    double height = 10.0;
    double area = lateral_surface_area_cylinder(radius, height);
    printf("Lateral Surface Area: %.15f\n", area);
    return 0;
}