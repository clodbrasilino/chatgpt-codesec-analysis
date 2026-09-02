#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double periodic_function(double x) {
    return sin(x) + 0.5 * cos(2 * x) + 0.25 * sin(4 * x);
}

double find_maximum(double period, int samples) {
    double max_value = -INFINITY;
    double x;
    int i;

    if (samples <= 0) {
        return -INFINITY;
    }

    for (i = 0; i < samples; i++) {
        x = (period * i) / samples;
        double value = periodic_function(x);
        if (value > max_value) {
            max_value = value;
        }
    }

    return max_value;
}

int main(void) {
    double period = 2 * M_PI;
    int samples = 100000;
    double max_val;

    max_val = find_maximum(period, samples);
    printf("Maximum value: %.10f\n", max_val);

    return 0;
}