#include <stdio.h>

double surface_area_of_cube(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    return 6.0 * side * side;
}

int main(void) {
    double side = 3.0;
    double area = surface_area_of_cube(side);
    
    if (area < 0.0) {
        return 1;
    }
    
    printf("%f\n", area);
    return 0;
}