#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6.285714285714286, got 5.6568541526794434
  *  test case 1 failed: expected 31.82142857142857, got 28.637825012207031
  */

double find_sector_area(double radius, double angle_degrees) {
    double angle_radians = (angle_degrees / 180.0) * M_PI;
    double area = 0.5 * radius * radius * sin(angle_radians);
    return area;
}

int main() {
    double radius, angle_degrees;
    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) return 1;

    printf("Enter the angle in degrees: ");
    if (scanf("%lf", &angle_degrees) != 1) return 1;

    double area = find_sector_area(radius, angle_degrees);
    printf("The area of the sector is: %.15f\n", area);

    return 0;
}