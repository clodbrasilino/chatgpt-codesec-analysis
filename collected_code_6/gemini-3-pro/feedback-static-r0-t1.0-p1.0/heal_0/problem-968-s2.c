#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double evaluate_function(double x) {
    return sin(x) + cos(2 * x);
}

double find_maximum_value(double start, double end, double step) {
    if (step <= 0 || start >= end) {
        return -INFINITY;
    }

    double max_val = -INFINITY;
    double current_x = start;

    while (current_x <= end) {
        double current_val = evaluate_function(current_x);
        if (current_val > max_val) {
            max_val = current_val;
        }
        current_x += step;
    }

    return max_val;
}

int main(void) {
    double start_interval = 0.0;
    double end_interval = 2 * PI;
    double step_size = 0.001;

    double max_value = find_maximum_value(start_interval, end_interval, step_size);

    if (max_value != -INFINITY) {
        printf("Maximum value: %.6f\n", max_value);
    } else {
        printf("Error calculating maximum value.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}