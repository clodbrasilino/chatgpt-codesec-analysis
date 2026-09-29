#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 880.5179353159282, got <no output>
  *  test case 0 failed: expected 282.7433388230814, got <no output>
  *  test case 2 failed: expected 2655.923961165254, got <no output>
  */

double surface_area_cone(double radius, double height) {
    double slant_height = sqrt(radius * radius + height * height);
    return M_PI * radius * (radius + slant_height);
}

int main() {
    double radius, height;
    if (scanf("%lf %lf", &radius, &height) == 2 && radius > 0 && height > 0) {
        double area = surface_area_cone(radius, height);
        printf("%.2f\n", area);
    } else {
        fprintf(stderr, "Invalid input. Please enter positive values for radius and height.\n");
        return 1;
    }
    return 0;
}