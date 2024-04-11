#include <stdio.h>

double sqrt_babylonian(double num) {
    double x = num;
    double y = 1;
    double e = 0.000001;

    while (x - y > e) {
        x = (x + y) / 2;
        y = num / x;
    }

    return x;
}

int main() {
    double num = 16;
    printf("Square root of %f is %f", num, sqrt_babylonian(num));
    return 0;
}