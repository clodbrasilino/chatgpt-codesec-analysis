#include <stdio.h>
#include <stdlib.h>

double calculate_perimeter(int sides, double length) {
    if (sides < 3) {
        return -1.0;
    }
    if (length <= 0.0) {
        return -1.0;
    }
    return (double)sides * length;
}

int main(int argc, char *argv[]) {
    int sides = 5;
    double length = 4.5;
    double perimeter = calculate_perimeter(sides, length);
    if (perimeter < 0.0) {
        return EXIT_FAILURE;
    }
    printf("%f\n", perimeter);
    return EXIT_SUCCESS;
}