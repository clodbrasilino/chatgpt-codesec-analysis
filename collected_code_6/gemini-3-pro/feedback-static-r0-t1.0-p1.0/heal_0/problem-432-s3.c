#include <stdio.h>
#include <stdlib.h>

double calculate_trapezium_median(double base_a, double base_b);

double calculate_trapezium_median(double base_a, double base_b) {
    if (base_a < 0.0 || base_b < 0.0) {
        return -1.0;
    }
    return (base_a + base_b) / 2.0;
}

int main(void) {
    double base_a = 0.0;
    double base_b = 0.0;
    double median = 0.0;
    int scan_result = 0;

    scan_result = scanf("%lf %lf", &base_a, &base_b);

    if (scan_result != 2) {
        return EXIT_FAILURE;
    }

    median = calculate_trapezium_median(base_a, base_b);

    if (median < 0.0) {
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}