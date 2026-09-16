#include <stdio.h>
#include <stdlib.h>

double calculate_perimeter(double length, double width) {
    if (length <= 0.0 || width <= 0.0) {
        return -1.0;
    }
    return 2.0 * (length + width);
}

int main(void) {
    double length = 0.0;
    double width = 0.0;
    double perimeter = 0.0;

    if (scanf("%lf %lf", &length, &width) != 2) {
        return EXIT_FAILURE;
    }

    perimeter = calculate_perimeter(length, width);

    if (perimeter < 0.0) {
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}