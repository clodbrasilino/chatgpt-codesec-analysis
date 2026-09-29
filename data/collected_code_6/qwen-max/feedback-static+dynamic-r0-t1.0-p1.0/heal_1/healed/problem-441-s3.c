#include <stdio.h>

double surface_area_of_cube(double side) {
    return 6 * side * side;
}

int main() {
    double sides[] = {5.0, 3.0, 10.0};
    for (int i = 0; i < 3; i++) {
        double area = surface_area_of_cube(sides[i]);
        printf("Surface Area: %f\n", area);
    }
    return 0;
}