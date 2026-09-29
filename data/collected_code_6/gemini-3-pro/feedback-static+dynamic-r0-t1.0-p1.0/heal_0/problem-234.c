#include <stdio.h>
#include <stdlib.h>

double calculate_cube_volume(double side_length) {
    if (side_length < 0.0) {
        return -1.0;
    }
    return side_length * side_length * side_length;
}

int main(void) {
    double side = 0.0;
    double volume = 0.0;
    int read_count = 0;

    printf("Enter the side length of the cube: ");
    read_count = scanf("%lf", &side);

    if (read_count != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cube_volume(side);

    if (volume < 0.0) {
        fprintf(stderr, "Error: Side length cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("The volume of the cube is: %.2f\n", volume);

    return EXIT_SUCCESS;
}