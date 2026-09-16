#include <stdio.h>

double lateral_surface_area_cube(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    return 4.0 * side * side;
}

int main() {
    double side = 5.0;
    double area = lateral_surface_area_cube(side);
    if (area >= 0.0) {
        printf("%f\n", area);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}