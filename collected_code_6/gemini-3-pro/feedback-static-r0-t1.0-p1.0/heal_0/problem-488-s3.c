#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calculate_pentagon_area(double side);

double calculate_pentagon_area(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    return 0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) * side * side;
}

int main(void) {
    double side = 0.0;
    double area = 0.0;
    int input_status = 0;

    input_status = scanf("%lf", &side);
    if (input_status != 1) {
        return EXIT_FAILURE;
    }

    area = calculate_pentagon_area(side);
    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    if (printf("%f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}