#include <stdio.h>
#include <stdlib.h>

double calculate_cube_volume(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    if (side > 1e102) {
        return -1.0;
    }
    return side * side * side;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    double side = strtod(argv[1], &endptr);
    
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    double volume = calculate_cube_volume(side);
    
    if (volume < 0.0) {
        return EXIT_FAILURE;
    }
    
    printf("%.6f\n", volume);
    
    return EXIT_SUCCESS;
}