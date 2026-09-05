#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_pentagon_area(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    return (sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) * side * side) / 4.0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    double side = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        return EXIT_FAILURE;
    }

    double area = calculate_pentagon_area(side);

    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}