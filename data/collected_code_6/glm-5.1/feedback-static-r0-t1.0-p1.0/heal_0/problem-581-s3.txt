#include <stdio.h>
#include <math.h>

double square_pyramid_surface_area(double base, double slant_height) {
    if (base < 0.0 || slant_height < 0.0) {
        return -1.0;
    }
    return (base * base) + (2.0 * base * slant_height);
}

int main(void) {
    double base = 4.0;
    double slant_height = 5.0;
    double area = square_pyramid_surface_area(base, slant_height);
    if (area < 0.0) {
        return 1;
    }
    printf("%f\n", area);
    return 0;
}