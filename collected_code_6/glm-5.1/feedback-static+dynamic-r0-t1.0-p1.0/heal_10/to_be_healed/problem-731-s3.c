#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 204.20352248333654, got 267.03536987304688
  *  test case 2 failed: expected 1521.8090132193388, got 2148.849365234375
  *  test case 1 failed: expected 566.3586699569488, got 785.398193359375
  */

double lateral_surface_area_cone(double radius, double slant_height) {
    if (radius < 0.0 || slant_height < 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius + M_PI * radius * slant_height;
}

int main(void) {
    double r, l;
    if (scanf("%lf %lf", &r, &l) == 2) {
        double area = lateral_surface_area_cone(r, l);
        if (area >= 0.0) {
            printf("%.10f\n", area);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}