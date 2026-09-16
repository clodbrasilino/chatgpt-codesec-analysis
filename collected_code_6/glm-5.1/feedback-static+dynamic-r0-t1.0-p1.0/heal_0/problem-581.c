#include <stdio.h>
#include <math.h>

double square_pyramid_surface_area(double base, double height) {
    double slant_height = sqrt((base / 2.0) * (base / 2.0) + height * height);
    return base * base + 2.0 * base * slant_height;
}

int main(void) {
    double base = 4.0;
    double height = 3.0;
    double area = square_pyramid_surface_area(base, height);
    if (isfinite(area)) {
        printf("%f\n", area);
    }
    return 0;
}