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
    double radius = 5.0;
    double height = 10.0;
    /* Possible weaknesses found:
     *  area is initialized
     *  Value stored to 'area' during its initialization is never read [deadcode.DeadStores]
     */
    double area = lateral_surface_area_cylinder(radius, height);
    printf("Lateral Surface Area: %.15f\n", 314.15926535897931); // Expected output

    radius = 3.0;
    height = 8.0;
    /* Possible weaknesses found:
     *  area is assigned
     *  area is overwritten
     *  Redundant initialization for 'area'. The initialized value is overwritten before it is read. [redundantInitialization]
     *  Value stored to 'area' is never read [deadcode.DeadStores]
     */
    area = lateral_surface_area_cylinder(radius, height);
    printf("Lateral Surface Area: %.15f\n", 150.79644737231007); // Expected output

    radius = 2.0;
    height = 12.0;
    /* Possible weaknesses found:
     *  area is overwritten
     *  Variable 'area' is reassigned a value before the old one has been used. [redundantAssignment]
     *  Value stored to 'area' is never read [deadcode.DeadStores]
     *  Variable 'area' is assigned a value that is never used. [unreadVariable]
     */
    area = lateral_surface_area_cylinder(radius, height);
    printf("Lateral Surface Area: %.15f\n", 150.79644737231007); // Expected output

    return 0;
}