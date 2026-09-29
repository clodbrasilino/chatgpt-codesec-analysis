#include <stdio.h>

double cube_volume(double side_length) {
    return side_length * side_length * side_length;
}

int main() {
    double side_length = 5.0;
    double volume = cube_volume(side_length);
    printf("Volume of the cube: %f\n", volume);
    return 0;
}