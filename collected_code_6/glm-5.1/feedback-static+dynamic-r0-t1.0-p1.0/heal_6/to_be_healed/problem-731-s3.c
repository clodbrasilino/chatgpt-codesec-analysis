#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1521.8090132193388, got <no output>
  *  test case 1 failed: expected 566.3586699569488, got <no output>
  *  test case 0 failed: expected 204.20352248333654, got <no output>
  */

double lateral_surface_area_cone(double radius, double slant_height) {
    if (radius < 0.0 || slant_height < 0.0) {
        return -1.0;
    }
    return M_PI * radius * slant_height;
}

int main(void) {
    double r, l;
    if (scanf("%lf %lf", &r, &l) == 2) {
        double area = lateral_surface_area_cone(r, l);
        if (area >= 0.0) {
            printf("%.10f\n", area);
        }
    }
    return 0;
}