#include <stdio.h>
#include <math.h>

double findMax(double a, double b, double c, double d, double start, double end) {
    double step = 0.001;
    double max_val = a * sin(b * start + c) + d;
    double x, y;

    for(x = start; x <= end; x += step) {
        y = a * sin(b * x + c) + d;
        if(y > max_val) {
            max_val = y;
        }
    }

    return max_val;
}

int main() {
    double a = 2.0, b = 3.0, c = 4.0, d = 5.0;
    double start = 0.0, end = 2 * M_PI;
    double max_val = findMax(a, b, c, d, start, end);

    printf("The maximum value of the function is: %f\n", max_val);

    return 0;
}