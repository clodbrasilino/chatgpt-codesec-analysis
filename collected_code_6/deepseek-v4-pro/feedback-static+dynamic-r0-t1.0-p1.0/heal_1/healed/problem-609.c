#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double periodic_function(double x) {
    return sin(x) + 0.5 * cos(2 * x) + 0.25 * sin(3 * x);
}

double find_minimum(double (*func)(double), double start, double end, int samples) {
    double min_x = start;
    double min_val = func(start);
    double step = (end - start) / samples;

    for (int i = 1; i <= samples; i++) {
        double x = start + i * step;
        double val = func(x);
        if (val < min_val) {
            min_val = val;
            min_x = x;
        }
    }

    double left = min_x - step;
    double right = min_x + step;

    for (int i = 0; i < 100; i++) {
        double mid = (left + right) / 2.0;
        double val_left = func(left);
        double val_right = func(right);
        double val_mid = func(mid);

        if (val_mid < val_left && val_mid < val_right) {
            if (val_left < val_right) {
                right = mid;
            } else {
                left = mid;
            }
        } else if (val_left < val_right) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return func((left + right) / 2.0);
}

int main(void) {
    double min_val = find_minimum(periodic_function, 0.0, 2.0 * M_PI, 1000);
    printf("%.10f\n", min_val);
    return 0;
}