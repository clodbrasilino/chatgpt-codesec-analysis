#include <stdio.h>
#include <math.h>

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