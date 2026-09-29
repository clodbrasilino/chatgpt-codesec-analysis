#include <stdio.h>
#include <stdlib.h>

double calculate_parallelogram_area(double base, double height) {
    if (base < 0.0 || height < 0.0) {
        return -1.0;
    }
    return base * height;
}

int main(void) {
    double base = 0.0;
    double height = 0.0;
    double area = 0.0;

    if (printf("Enter base: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &base) != 1) {
        return EXIT_FAILURE;
    }

    if (printf("Enter height: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &height) != 1) {
        return EXIT_FAILURE;
    }

    area = calculate_parallelogram_area(base, height);

    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    if (printf("Area: %f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}