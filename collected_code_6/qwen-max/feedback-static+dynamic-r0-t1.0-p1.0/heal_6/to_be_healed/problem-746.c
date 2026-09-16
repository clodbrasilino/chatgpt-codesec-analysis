#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6.285714285714286, got 360
  *  test case 1 failed: expected 31.82142857142857, got 1822.5
  */

double find_sector_area(double radius, double angle) {
    if (radius < 0 || angle < 0 || angle > 360) {
        return -1;
    }
    return (M_PI * pow(radius, 2) * (angle / 360.0)) * (180.0 / M_PI);
}

int main() {
    double radius = 5.0;
    double angle = 90.0;
    double area = find_sector_area(radius, angle);
    if (area >= 0) {
        printf("Area of the sector: %.15f\n", area);
    } else {
        printf("Invalid input for radius or angle.\n");
    }
    return 0;
}