#include <stdio.h>
#include <stdlib.h>

double cube_volume(double side) {
    if (side <= 0.0) {
        fprintf(stderr, "Error: side length must be positive\n");
        exit(EXIT_FAILURE);
    }
    return side * side * side;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double side;
    double volume;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    side = atof(argv[1]);
    volume = cube_volume(side);

    printf("%.6f\n", volume);

    return EXIT_SUCCESS;
}