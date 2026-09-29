#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double cone_surface_area(double radius, double slant_height) {
    return PI * radius * (radius + slant_height);
}

int main(void) {
    double radius, slant_height, area;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1 || radius <= 0) {
        fprintf(stderr, "Invalid radius\n");
        return 1;
    }

    printf("Enter slant height: ");
    if (scanf("%lf", &slant_height) != 1 || slant_height <= 0) {
        fprintf(stderr, "Invalid slant height\n");
        return 1;
    }

    area = cone_surface_area(radius, slant_height);

    printf("Surface area of cone: %.2f\n", area);
    return 0;
}