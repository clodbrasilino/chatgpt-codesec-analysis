#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 251.32000000000002, got 251.32740783691406
  *  test case 1 failed: expected 125.66000000000001, got 125.66370391845703
  *  test case 0 failed: expected 314.15000000000003, got 314.15927124023438
  */

double lateral_surface_area_cylinder(double radius, double height) {
    return 2.0 * M_PI * radius * height;
}

int main() {
    double radius = 5.0;
    double height = 10.0;

    double area = lateral_surface_area_cylinder(radius, height);
    printf("The lateral surface area of the cylinder with radius %.1f and height %.1f is: %.15f\n", radius, height, area);

    radius = 2.0;
    height = 20.0;
    area = lateral_surface_area_cylinder(radius, height);
    printf("The lateral surface area of the cylinder with radius %.1f and height %.1f is: %.15f\n", radius, height, area);

    radius = 1.0;
    height = 40.0;
    area = lateral_surface_area_cylinder(radius, height);
    printf("The lateral surface area of the cylinder with radius %.1f and height %.1f is: %.15f\n", radius, height, area);

    radius = 1.0;
    height = 80.0;
    area = lateral_surface_area_cylinder(radius, height);
    printf("The lateral surface area of the cylinder with radius %.1f and height %.1f is: %.15f\n", radius, height, area);

    return 0;
}