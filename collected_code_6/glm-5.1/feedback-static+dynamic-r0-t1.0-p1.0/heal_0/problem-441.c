#include <stdio.h>

double calculate_cube_surface_area(double side_length) {
    if (side_length < 0.0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double side = 3.0;
    double area = calculate_cube_surface_area(side);

    if (area < 0.0) {
        return 1;
    }

    printf("%f\n", area);
    return 0;
}