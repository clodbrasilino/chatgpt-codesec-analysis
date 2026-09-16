#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_regular_polygon_area(int sides, double length) {
    if (sides < 3) {
        return 0.0;
    }
    if (length <= 0.0) {
        return 0.0;
    }
    double area = (sides * length * length) / (4.0 * tan(M_PI / sides));
    if (!isfinite(area)) {
        return 0.0;
    }
    return area;
}

int main(void) {
    int sides = 5;
    double length = 5.0;
    double area = calculate_regular_polygon_area(sides, length);
    printf("%f\n", area);
    return 0;
}