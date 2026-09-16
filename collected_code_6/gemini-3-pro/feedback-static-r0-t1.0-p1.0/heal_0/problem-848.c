#include <stdio.h>
#include <stdlib.h>

double calculate_trapezium_area(double a, double b, double h) {
    if (a < 0.0 || b < 0.0 || h < 0.0) {
        return -1.0;
    }
    return ((a + b) / 2.0) * h;
}

int main(void) {
    double a;
    double b;
    double h;
    double area;
    int result;

    result = scanf("%lf %lf %lf", &a, &b, &h);

    if (result != 3) {
        return EXIT_FAILURE;
    }

    area = calculate_trapezium_area(a, b, h);

    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}