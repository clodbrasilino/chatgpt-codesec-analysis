#include <stdio.h>
#include <math.h>

double square_pyramid_surface_area(double base_edge, double slant_height) {
    if (base_edge <= 0 || slant_height <= 0) {
        return -1.0;
    }
    double base_area = base_edge * base_edge;
    double lateral_area = 2.0 * base_edge * slant_height;
    return base_area + lateral_area;
}

int main(void) {
    double base_edge, slant_height;
    printf("Enter base edge length: ");
    if (scanf("%lf", &base_edge) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter slant height: ");
    if (scanf("%lf", &slant_height) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    double area = square_pyramid_surface_area(base_edge, slant_height);
    if (area < 0) {
        printf("Invalid dimensions\n");
        return 1;
    }
    printf("Surface area: %.2f\n", area);
    return 0;
}