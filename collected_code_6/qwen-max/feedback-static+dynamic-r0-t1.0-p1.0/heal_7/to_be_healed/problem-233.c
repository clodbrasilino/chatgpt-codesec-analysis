#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 251.32000000000002, got 251.32740783691406
  *  test case 1 failed: expected 125.66000000000001, got 125.66370391845703
  *  test case 0 failed: expected 314.15000000000003, got 314.15927124023438
  */

double lateral_surface_area_cylinder(double radius, double height) {
    return 2 * M_PI * radius * height;
}

int main() {
    double radius = 10.0;
    double height = 10.0;
    printf("Lateral Surface Area: %.15f\n", lateral_surface_area_cylinder(radius, height));

    radius = 5.0;
    height = 8.0;
    printf("Lateral Surface Area: %.15f\n", lateral_surface_area_cylinder(radius, height));

    radius = 4.0;
    height = 12.0;
    printf("Lateral Surface Area: %.15f\n", lateral_surface_area_cylinder(radius, height));

    return 0;
}