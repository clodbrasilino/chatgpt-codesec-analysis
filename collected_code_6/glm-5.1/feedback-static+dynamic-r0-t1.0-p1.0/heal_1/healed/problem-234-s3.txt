#include <stdio.h>
#include <stdlib.h>

double calculate_cube_volume(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    return side * side * side;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double side = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: Not a valid number\n");
        return EXIT_FAILURE;
    }

    double volume = calculate_cube_volume(side);

    if (volume < 0.0) {
        fprintf(stderr, "Invalid input: Side length cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", volume);

    return EXIT_SUCCESS;
}