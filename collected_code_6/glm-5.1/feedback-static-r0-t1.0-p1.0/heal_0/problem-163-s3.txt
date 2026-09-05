#include <stdio.h>
#include <math.h>

double calculate_regular_polygon_area(int num_sides, double side_length) {
    if (num_sides < 3 || side_length <= 0.0) {
        return NAN;
    }
    return (num_sides * side_length * side_length) / (4.0 * tan(M_PI / num_sides));
}

int main() {
    int sides = 6;
    double length = 5.0;
    double area = calculate_regular_polygon_area(sides, length);
    if (isnan(area)) {
        return 1;
    }
    printf("%f\n", area);
    return 0;
}