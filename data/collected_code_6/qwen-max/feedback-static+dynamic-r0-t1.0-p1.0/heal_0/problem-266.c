#include <stdio.h>

double lateral_surface_area(double side) {
    return 4.0 * side * side;
}

int main() {
    double side = 5.0;
    printf("Lateral Surface Area: %.2f\n", lateral_surface_area(side));
    return 0;
}