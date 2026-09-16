#include <stdio.h>
#include <stdlib.h>

double current_area(double a, double b, double h) {
    if (a < 0.0 || b < 0.0 || h < 0.0) {
        return -1.0;
    }
    return ((a + b) / 2.0) * h;
}

int main(void) {
    double base1 = 0.0;
    double base2 = 0.0;
    double height = 0.0;
    double area = 0.0;
    int result = 0;

    result = scanf("%lf %lf %lf", &base1, &base2, &height);
    if (result != 3) {
        return EXIT_FAILURE;
    }

    area = current_area(base1, base2, height);
    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", area);
    return EXIT_SUCCESS;
}