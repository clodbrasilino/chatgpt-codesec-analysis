#include <stdio.h>

double volume_of_cube(double side) {
    return side * side * side;
}

int main() {
    double side = 5.0;
    printf("Volume of the cube: %f\n", volume_of_cube(side));
    return 0;
}