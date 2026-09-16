#include <stdio.h>
#include <stdlib.h>

double calculate_perimeter(int sides, double length) {
    if (sides < 3) {
        return -1.0;
    }
    if (length < 0.0) {
        return -1.0;
    }
    return (double)sides * length;
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_sides> <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_sides;
    long sides_long = strtol(argv[1], &endptr_sides, 10);
    if (*endptr_sides != '\0' || sides_long < 3) {
        fprintf(stderr, "Error: Number of sides must be an integer >= 3.\n");
        return EXIT_FAILURE;
    }

    char *endptr_length;
    double length = strtod(argv[2], &endptr_length);
    if (*endptr_length != '\0' || length < 0.0) {
        fprintf(stderr, "Error: Side length must be a non-negative number.\n");
        return EXIT_FAILURE;
    }

    double perimeter = calculate_perimeter((int)sides_long, length);
    
    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Invalid polygon parameters.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", perimeter);
    return EXIT_SUCCESS;
}