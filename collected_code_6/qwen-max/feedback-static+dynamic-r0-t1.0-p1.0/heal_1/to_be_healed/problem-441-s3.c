#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 600, got <no output>
  *  test case 1 failed: expected 54, got <no output>
  *  test case 0 failed: expected 150, got <no output>
  */

double surface_area_of_cube(double side) {
    return 6 * side * side;
}

int main() {
    double side = 5.0;
    double area = surface_area_of_cube(side);
    printf("Surface Area: %f\n", area);
    return 0;
}