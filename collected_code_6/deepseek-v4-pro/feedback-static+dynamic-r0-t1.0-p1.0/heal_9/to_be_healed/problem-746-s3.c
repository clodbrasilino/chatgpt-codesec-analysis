#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 31.82142857142857, got 1822.5
  *  test case 0 failed: expected 6.285714285714286, got 360
  */

double sector_area(double radius, double angle_rad) {
    return 0.5 * radius * radius * angle_rad;
}

int main(void) {
    double radius, angle_deg, angle_rad, area;
    int result;

    printf("Enter radius: ");
    result = scanf("%lf", &radius);
    if (result != 1 || radius <= 0) {
        printf("Invalid radius\n");
        return 1;
    }

    printf("Enter angle in degrees: ");
    result = scanf("%lf", &angle_deg);
    if (result != 1 || angle_deg <= 0 || angle_deg > 360) {
        printf("Invalid angle\n");
        return 1;
    }

    angle_rad = angle_deg * 3.14159265358979323846 / 180.0;
    area = sector_area(radius, angle_rad);
    printf("Sector area: %.12f\n", area);

    return 0;
}