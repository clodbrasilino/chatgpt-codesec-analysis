#include <stdio.h>
#include <stdlib.h>

double calculate_pentagon_perimeter(double side_length) {
    if (side_length < 0.0) {
        exit(EXIT_FAILURE);
    }
    return 5.0 * side_length;
}

int main(void) {
    double side;
    if (scanf("%lf", &side) != 1) {
        return EXIT_FAILURE;
    }
    double perimeter = calculate_pentagon_perimeter(side);
    printf("%f\n", perimeter);
    return EXIT_SUCCESS;
}