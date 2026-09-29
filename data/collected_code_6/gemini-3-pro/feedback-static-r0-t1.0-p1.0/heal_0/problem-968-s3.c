#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define NUM_STEPS 100000

double target_function(double x) {
    return sin(x) + cos(0.5 * x);
}

double find_maximum_value(double start, double end) {
    if (start >= end) {
        return -INFINITY;
    }

    double max_val = target_function(start);
    double step = (end - start) / NUM_STEPS;
    double current_x = start;

    for (int i = 1; i <= NUM_STEPS; ++i) {
        current_x += step;
        double current_val = target_function(current_x);
        if (current_val > max_val) {
            max_val = current_val;
        }
    }

    return max_val;
}

int main(void) {
    double period_start = 0.0;
    double period_end = 4.0 * PI; 

    double max_val = find_maximum_value(period_start, period_end);

    if (max_val != -INFINITY) {
        printf("Maximum value: %f\n", max_val);
    } else {
        printf("Invalid range.\n");
        return 1;
    }

    return 0;
}