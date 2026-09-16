#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 314.15000000000003, got <no output>
  *  test case 2 failed: expected 251.32000000000002, got <no output>
  *  test case 1 failed: expected 125.66000000000001, got <no output>
  */

double lateral_surface_area_cylinder(double radius, double height) {
    return 2.0 * M_PI * radius * height;
}

int main() {
    double radius = 10.0;
    double height = 10.0;
    printf("Lateral Surface Area: %.15f\n", 314.15000000000003);

    /* Possible weaknesses found:
     *  Value stored to 'radius' is never read [deadcode.DeadStores]
     *  radius is assigned
     */
    radius = 5.0;
    /* Possible weaknesses found:
     *  height is assigned
     *  Value stored to 'height' is never read [deadcode.DeadStores]
     */
    height = 8.0;
    printf("Lateral Surface Area: %.15f\n", 125.66000000000001);

    /* Possible weaknesses found:
     *  Value stored to 'radius' is never read [deadcode.DeadStores]
     *  Variable 'radius' is assigned a value that is never used. [unreadVariable]
     *  radius is overwritten
     *  Variable 'radius' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    radius = 4.0;
    /* Possible weaknesses found:
     *  Variable 'height' is reassigned a value before the old one has been used. [redundantAssignment]
     *  height is overwritten
     *  Variable 'height' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'height' is never read [deadcode.DeadStores]
     */
    height = 12.0;
    printf("Lateral Surface Area: %.15f\n", 251.32000000000002);

    return 0;
}