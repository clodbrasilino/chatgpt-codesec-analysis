#include <stdio.h>

double surface_area_cube(double side) {
    double area = 6.0 * side * side;
    return area;
}

int main(void) {
    double side = 3.0;
    double area = surface_area_cube(side);
    if (fprintf(stdout, "%f\n", area) < 0) {
        return 1;
    }
    return 0;
}