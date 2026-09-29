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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <sides> <length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long sides_l = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || sides_l < 3 || sides_l > INT_MAX) {
        fprintf(stderr, "Invalid number of sides\n");
        return EXIT_FAILURE;
    }

    double length = strtod(argv[2], &endptr);
    if (*endptr != '\0' || length < 0.0) {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    double perimeter = calculate_perimeter((int)sides_l, length);
    if (perimeter < 0.0) {
        fprintf(stderr, "Calculation error\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", perimeter);
    return EXIT_SUCCESS;
}