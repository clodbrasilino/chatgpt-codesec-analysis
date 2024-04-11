#include <stdio.h>
#include <math.h>

double findMax(double a, double b, double c) {
    double max = a;
    for(double x = b; x <= c; x += 0.01) {
        double val = sin(x);
        if(val > max) {
            max = val;
        }
    }
    return max;
}

int main() {
    double a = -1;
    double b = 0;
    double c = 2 * M_PI;
    double max = findMax(a, b, c);
    printf("Maximum value is: %f\n", max);
    return 0;
}