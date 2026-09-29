#include <stdio.h>
#include <stdlib.h>

double calculate_pentagon_perimeter(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    return 5.0 * side;
}

int main(void) {
    double side = 0.0;
    double perimeter = 0.0;
    int result = 0;

    result = scanf("%lf", &side);

    if (result != 1) {
        return EXIT_FAILURE;
    }

    perimeter = calculate_pentagon_perimeter(side);

    if (perimeter < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", perimeter);

    return EXIT_SUCCESS;
}