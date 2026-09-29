#include <stdio.h>

double cube_volume(double side_length) {
    if (side_length <= 0) {
        return -1.0;
    }
    return side_length * side_length * side_length;
}

int main(void) {
    double side = 5.0;
    double volume = cube_volume(side);
    
    if (volume < 0) {
        fprintf(stderr, "Error: Invalid side length\n");
        return 1;
    }
    
    printf("Volume of cube with side %.2f: %.2f\n", side, volume);
    
    return 0;
}