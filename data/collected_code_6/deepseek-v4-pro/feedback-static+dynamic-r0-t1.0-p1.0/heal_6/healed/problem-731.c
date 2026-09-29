#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double lateral_surface_area(double radius, double slant_height) {
    return PI * radius * slant_height;
}

int main(void) {
    double radius, slant_height, area;

    if (scanf("%lf %lf", &radius, &slant_height) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (radius <= 0 || slant_height <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    area = lateral_surface_area(radius, slant_height);
    printf("%.13f\n", area);

    return 0;
}